#pragma once
#include "CoreMinimal.h"
#include "FMarketListing.h"
#include "UMarketplaceManager.generated.h"

class UInventoryComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnItemListed, int64, SellerID, const FString&, ItemID, FGuid, ListingID, int32, Price);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnItemSold, int64, SellerID, int64, BuyerID, const FString&, ItemID, int32, Price, int32, Payout, int32, Commission);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnSellerItemUnlocked, int64, SellerID, const FString&, ItemID, FGuid, ListingID, bool, bSold);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnListingCancelled, int64, SellerID, FGuid, ListingID, const FString&, ItemID);

UCLASS(BlueprintType)
class ATOMICHEARTS_API UMarketplaceManager : public UObject {
    GENERATED_BODY()

public:
    static constexpr int32 LISTING_FEE = 10;
    static constexpr int32 MAX_LISTINGS_PER_PLAYER = 20;
    static constexpr int64 RELIST_COOLDOWN_SECONDS = 86400;

    /** Inject inventory component for ownership checks */
    void SetInventoryComponent(UInventoryComponent* Inventory) { InventoryComponent = Inventory; }

    /** Events for external systems (currency, inventory) to bind to */
    UPROPERTY(BlueprintAssignable)
    FOnItemListed OnItemListed;

    UPROPERTY(BlueprintAssignable)
    FOnItemSold OnItemSold;

    UPROPERTY(BlueprintAssignable)
    FOnListingCancelled OnListingCancelled;

    /** Fired on seller client: unlock their item (bSold=true if sold, false if cancelled) */
    UPROPERTY(BlueprintAssignable)
    FOnSellerItemUnlocked OnSellerItemUnlocked;

    /** List an item for sale. Verifies ownership via inventory. */
    UFUNCTION(BlueprintCallable)
    FMarketListing ListItem(int64 SellerID, const FString& ItemID,
                            const FString& ItemName, EItemType ItemType,
                            EWeaponRarity Rarity, int32 Price);

    /** Purchase: Deduct from buyer, credit seller, remove listing, unlock item. */
    UFUNCTION(BlueprintCallable)
    bool PurchaseItem(FGuid ListingID, int64 BuyerID);

    UFUNCTION(BlueprintPure)
    int32 CalculateCommission(int32 SalePrice) const { return FMath::CeilToInt(SalePrice * 0.30f); }

    UFUNCTION(BlueprintPure)
    int32 CalculateSellerPayout(int32 SalePrice) const {
        return FMath::FloorToInt((SalePrice - LISTING_FEE) * 0.70f);
    }

    UFUNCTION(BlueprintCallable)
    bool CancelListing(FGuid ListingID);

    UFUNCTION(BlueprintCallable)
    TArray<FMarketListing> GetListings(EItemType FilterType = EItemType::None,
                                       EWeaponRarity MinRarity = EWeaponRarity::Common,
                                       int32 MaxPrice = MAX_int32) const;

    UFUNCTION(BlueprintPure)
    bool CanListItem(int64 SellerID) const;

    UFUNCTION(BlueprintPure)
    int32 GetListingFee() const { return LISTING_FEE; }

    UFUNCTION(BlueprintPure)
    int32 GetMaxListingsPerPlayer() const { return MAX_LISTINGS_PER_PLAYER; }

private:
    UPROPERTY()
    TArray<FMarketListing> Listings;

    UPROPERTY()
    TMap<int64, int64> PlayerLastListTime;

    /** Cached listing -> item for unlock on cancel/sale */
    UPROPERTY()
    TMap<FGuid, FString> ListingToItem;

    UPROPERTY()
    TMap<int64, TSet<FGuid>> PlayerActiveListings;

    UPROPERTY()
    UInventoryComponent* InventoryComponent = nullptr;

    bool VerifyOwnership(int64 SellerID, const FString& ItemID) const;
    void LockItem(int64 SellerID, const FString& ItemID);
    void UnlockItem(int64 SellerID, const FString& ItemID);

    FGuid GenerateListingID() const;
    int64 GetCurrentTimestamp() const;
    int32 GetActiveListingCount(int64 SellerID) const;
    bool IsOnCooldown(int64 SellerID) const;
    FMarketListing* FindListing(FGuid ListingID);
    const FMarketListing* FindListing(FGuid ListingID) const;
};
