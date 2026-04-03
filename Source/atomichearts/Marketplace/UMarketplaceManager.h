#pragma once
#include "CoreMinimal.h"
#include "FMarketListing.h"
#include "UMarketplaceManager.generated.h"

UCLASS(BlueprintType)
class UMarketplaceManager : public UObject {
    GENERATED_BODY()

public:
    static constexpr int32 LISTING_FEE = 10;
    static constexpr int32 MAX_LISTINGS_PER_PLAYER = 20;
    static constexpr int64 RELIST_COOLDOWN_SECONDS = 86400; // 24 hours

    /** List an item for sale. Returns invalid listing if failed. */
    UFUNCTION(BlueprintCallable)
    FMarketListing ListItem(int64 SellerID, const FString& ItemID,
                            const FString& ItemName, EItemType ItemType,
                            EWeaponRarity Rarity, int32 Price);

    /** Purchase an item from a listing. Returns true on success. */
    UFUNCTION(BlueprintCallable)
    bool PurchaseItem(FGuid ListingID, int64 BuyerID);

    /** Calculate commission: 30% of sale price. */
    UFUNCTION(BlueprintPure)
    int32 CalculateCommission(int32 SalePrice) const;

    /** Calculate seller payout: 70% of (SalePrice - LISTING_FEE). */
    UFUNCTION(BlueprintPure)
    int32 CalculateSellerPayout(int32 SalePrice) const;

    /** Cancel a listing and unlock the item. */
    UFUNCTION(BlueprintCallable)
    bool CancelListing(FGuid ListingID);

    /** Get all listings filtered by type, rarity, and max price. */
    UFUNCTION(BlueprintCallable)
    TArray<FMarketListing> GetListings(EItemType FilterType = EItemType::None,
                                       EWeaponRarity MinRarity = EWeaponRarity::Common,
                                       int32 MaxPrice = MAX_int32) const;

    /** Check if a player can list (under limit, no cooldown). */
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
    TMap<int64, int64> PlayerLastListTime; // SellerID -> Timestamp

    FGuid GenerateListingID() const;
    int64 GetCurrentTimestamp() const;
    int32 GetActiveListingCount(int64 SellerID) const;
    bool IsOnCooldown(int64 SellerID) const;
    FMarketListing* FindListing(FGuid ListingID);
    const FMarketListing* FindListing(FGuid ListingID) const;
};
