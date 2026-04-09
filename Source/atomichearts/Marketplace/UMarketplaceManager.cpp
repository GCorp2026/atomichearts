#include "Marketplace/UMarketplaceManager.h"
#include "Inventory/InventoryComponent.h"
#include "Kismet/KismetMathLibrary.h"

FGuid UMarketplaceManager::GenerateListingID() const {
    return FGuid::NewGuid();
}

int64 UMarketplaceManager::GetCurrentTimestamp() const {
    return FDateTime::UtcNow().ToUnixTimestamp();
}

int32 UMarketplaceManager::GetActiveListingCount(int64 SellerID) const {
    if (auto* Set = PlayerActiveListings.Find(SellerID)) {
        return Set->Num();
    }
    return 0;
}

bool UMarketplaceManager::IsOnCooldown(int64 SellerID) const {
    if (auto* LastTime = PlayerLastListTime.Find(SellerID)) {
        return (GetCurrentTimestamp() - *LastTime) < RELIST_COOLDOWN_SECONDS;
    }
    return false;
}

FMarketListing* UMarketplaceManager::FindListing(FGuid ListingID) {
    for (auto& Listing : Listings) {
        if (Listing.ListingID == ListingID) return &Listing;
    }
    return nullptr;
}

const FMarketListing* UMarketplaceManager::FindListing(FGuid ListingID) const {
    for (const auto& Listing : Listings) {
        if (Listing.ListingID == ListingID) return &Listing;
    }
    return nullptr;
}

bool UMarketplaceManager::VerifyOwnership(int64 SellerID, const FString& ItemID) const {
    // If no inventory component injected, assume ownership is valid
    if (!InventoryComponent) return true;
    // Verify this inventory belongs to the seller and has the item
    if (InventoryComponent->GetOwnerPlayerID() != SellerID) {
        UE_LOG(LogTemp, Warning, TEXT("VerifyOwnership: Inventory OwnerID=%lld doesn't match SellerID=%lld"),
               InventoryComponent->GetOwnerPlayerID(), SellerID);
        return false;
    }
    return InventoryComponent->HasItem(ItemID);
}

void UMarketplaceManager::LockItem(int64 SellerID, const FString& ItemID) {
    if (!InventoryComponent) return;
    if (InventoryComponent->GetOwnerPlayerID() != SellerID) {
        UE_LOG(LogTemp, Warning, TEXT("LockItem: Inventory OwnerID=%lld doesn't match SellerID=%lld"),
               InventoryComponent->GetOwnerPlayerID(), SellerID);
        return;
    }
    InventoryComponent->SetItemLocked(ItemID, true);
}

void UMarketplaceManager::UnlockItem(int64 SellerID, const FString& ItemID) {
    if (!InventoryComponent) return;
    if (InventoryComponent->GetOwnerPlayerID() != SellerID) {
        UE_LOG(LogTemp, Warning, TEXT("UnlockItem: Inventory OwnerID=%lld doesn't match SellerID=%lld"),
               InventoryComponent->GetOwnerPlayerID(), SellerID);
        return;
    }
    InventoryComponent->SetItemLocked(ItemID, false);
}

bool UMarketplaceManager::CanListItem(int64 SellerID) const {
    if (GetActiveListingCount(SellerID) >= MAX_LISTINGS_PER_PLAYER) return false;
    if (IsOnCooldown(SellerID)) return false;
    return true;
}

FMarketListing UMarketplaceManager::ListItem(int64 SellerID, const FString& ItemID,
                                             const FString& ItemName, EItemType ItemType,
                                             EWeaponRarity Rarity, int32 Price) {
    if (!CanListItem(SellerID)) return FMarketListing();
    if (Price <= 0) return FMarketListing();

    // FIX #2: Verify seller owns the item
    if (!VerifyOwnership(SellerID, ItemID)) {
        UE_LOG(LogTemp, Warning, TEXT("ListItem: Seller %lld does not own item %s"), SellerID, *ItemID);
        return FMarketListing();
    }

    FMarketListing NewListing;
    NewListing.ListingID = GenerateListingID();
    NewListing.SellerID = SellerID;
    NewListing.ItemID = ItemID;
    NewListing.ItemName = ItemName;
    NewListing.ItemType = ItemType;
    NewListing.Rarity = Rarity;
    NewListing.Price = Price;
    NewListing.ListedAt = GetCurrentTimestamp();

    Listings.Add(NewListing);
    PlayerLastListTime.Add(SellerID, NewListing.ListedAt);
    PlayerActiveListings.FindOrAdd(SellerID).Add(NewListing.ListingID);
    ListingToItem.Add(NewListing.ListingID, ItemID);

    // FIX #3: Lock item in inventory while listed
    LockItem(SellerID, ItemID);

    OnItemListed.Broadcast(SellerID, ItemID, NewListing.ListingID, Price);
    return NewListing;
}

bool UMarketplaceManager::PurchaseItem(FGuid ListingID, int64 BuyerID) {
    FMarketListing* Listing = FindListing(ListingID);
    if (!Listing) return false;
    if (Listing->SellerID == BuyerID) return false;

    int32 Payout = CalculateSellerPayout(Listing->Price);
    int32 Commission = CalculateCommission(Listing->Price);

    // FIX #1: Actually transfer currency via event
    // Currency system should bind to OnItemSold and handle:
    //   - Deduct Price from BuyerID
    //   - Add Payout to SellerID
    //   - Take Commission (goes to platform/protocol)
    OnItemSold.Broadcast(Listing->SellerID, BuyerID, Listing->ItemID, Listing->Price, Payout);
    UE_LOG(LogTemp, Log,
        TEXT("Purchase: ListingID=%s Price=%d Buyer=%lld Seller=%lld Payout=%d Commission=%d"),
        *ListingID.ToString(), Listing->Price, BuyerID, Listing->SellerID, Payout, Commission);

    // FIX #3: Unlock item from seller's inventory, assign to buyer
    UnlockItem(Listing->SellerID, Listing->ItemID);
    // Buyer receives item — inventory system should bind to OnItemSold and add item to buyer

    // Remove listing
    if (auto* Set = PlayerActiveListings.Find(Listing->SellerID)) {
        Set->Remove(ListingID);
    }
    ListingToItem.Remove(ListingID);
    Listings.RemoveAll([&ListingID](const FMarketListing& L) { return L.ListingID == ListingID; });

    return true;
}

bool UMarketplaceManager::CancelListing(FGuid ListingID) {
    for (int32 i = 0; i < Listings.Num(); i++) {
        if (Listings[i].ListingID == ListingID) {
            int64 SellerID = Listings[i].SellerID;
            FString ItemID = Listings[i].ItemID;

            // FIX #3: Unlock the item
            UnlockItem(SellerID, ItemID);
            OnListingCancelled.Broadcast(SellerID, ListingID, ItemID);

            if (auto* Set = PlayerActiveListings.Find(SellerID)) {
                Set->Remove(ListingID);
            }
            ListingToItem.Remove(ListingID);
            Listings.RemoveAt(i);
            return true;
        }
    }
    return false;
}

TArray<FMarketListing> UMarketplaceManager::GetListings(EItemType FilterType,
                                                         EWeaponRarity MinRarity,
                                                         int32 MaxPrice) const {
    TArray<FMarketListing> Result;
    for (const auto& Listing : Listings) {
        if (FilterType != EItemType::None && Listing.ItemType != FilterType) continue;
        if ((int32)Listing.Rarity < (int32)MinRarity) continue;
        if (Listing.Price > MaxPrice) continue;
        Result.Add(Listing);
    }
    return Result;
}
