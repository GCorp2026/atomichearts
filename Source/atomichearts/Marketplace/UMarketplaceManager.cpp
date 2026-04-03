#include "Marketplace/UMarketplaceManager.h"
#include "Kismet/KismetMathLibrary.h"

FGuid UMarketplaceManager::GenerateListingID() const {
    return FGuid::NewGuid();
}

int64 UMarketplaceManager::GetCurrentTimestamp() const {
    return FDateTime::UtcNow().ToUnixTimestamp();
}

int32 UMarketplaceManager::GetActiveListingCount(int64 SellerID) const {
    int32 Count = 0;
    for (const auto& Listing : Listings) {
        if (Listing.SellerID == SellerID) {
            Count++;
        }
    }
    return Count;
}

bool UMarketplaceManager::IsOnCooldown(int64 SellerID) const {
    if (auto* LastTime = PlayerLastListTime.Find(SellerID)) {
        int64 Elapsed = GetCurrentTimestamp() - *LastTime;
        return Elapsed < RELIST_COOLDOWN_SECONDS;
    }
    return false;
}

FMarketListing* UMarketplaceManager::FindListing(FGuid ListingID) {
    for (auto& Listing : Listings) {
        if (Listing.ListingID == ListingID) {
            return &Listing;
        }
    }
    return nullptr;
}

const FMarketListing* UMarketplaceManager::FindListing(FGuid ListingID) const {
    for (const auto& Listing : Listings) {
        if (Listing.ListingID == ListingID) {
            return &Listing;
        }
    }
    return nullptr;
}

bool UMarketplaceManager::CanListItem(int64 SellerID) const {
    if (GetActiveListingCount(SellerID) >= MAX_LISTINGS_PER_PLAYER) {
        return false;
    }
    if (IsOnCooldown(SellerID)) {
        return false;
    }
    return true;
}

FMarketListing UMarketplaceManager::ListItem(int64 SellerID, const FString& ItemID,
                                               const FString& ItemName, EItemType ItemType,
                                               EWeaponRarity Rarity, int32 Price) {
    if (!CanListItem(SellerID)) {
        return FMarketListing();
    }
    if (Price <= 0) {
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
    return NewListing;
}

bool UMarketplaceManager::PurchaseItem(FGuid ListingID, int64 BuyerID) {
    FMarketListing* Listing = FindListing(ListingID);
    if (!Listing) {
        return false;
    }
    if (Listing->SellerID == BuyerID) {
        return false;
    }

    int32 Payout = CalculateSellerPayout(Listing->Price);
    int32 Commission = CalculateCommission(Listing->Price);
    UE_LOG(LogTemp, Log, TEXT("Purchase: ListingID=%s, Price=%d, SellerPayout=%d, Commission=%d"),
           *ListingID.ToString(), Listing->Price, Payout, Commission);

    Listings.RemoveAll([&ListingID](const FMarketListing& L) {
        return L.ListingID == ListingID;
    });
    return true;
}

int32 UMarketplaceManager::CalculateCommission(int32 SalePrice) const {
    return FMath::CeilToInt(SalePrice * 0.30f);
}

int32 UMarketplaceManager::CalculateSellerPayout(int32 SalePrice) const {
    // 70% of (SalePrice - LISTING_FEE), listing fee refunded on sale
    int32 AfterFee = SalePrice - LISTING_FEE;
    return FMath::FloorToInt(AfterFee * 0.70f);
}

bool UMarketplaceManager::CancelListing(FGuid ListingID) {
    for (int32 i = 0; i < Listings.Num(); i++) {
        if (Listings[i].ListingID == ListingID) {
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
        if (FilterType != EItemType::None && Listing.ItemType != FilterType) {
            continue;
        }
        if ((int32)Listing.Rarity < (int32)MinRarity) {
            continue;
        }
        if (Listing.Price > MaxPrice) {
            continue;
        }
        Result.Add(Listing);
    }
    return Result;
}
