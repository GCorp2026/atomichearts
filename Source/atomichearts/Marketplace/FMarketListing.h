#pragma once
#include "CoreMinimal.h"
#include "EItemType.h"
#include "EWeaponRarity.h"
#include "FMarketListing.generated.h"

USTRUCT(BlueprintType)
struct FMarketListing {
    GENERATED_BODY()

    UPROPERTY()
    FGuid ListingID;

    UPROPERTY()
    int64 SellerID;

    UPROPERTY()
    FString ItemID;

    UPROPERTY()
    FString ItemName;

    UPROPERTY()
    EItemType ItemType;

    UPROPERTY()
    EWeaponRarity Rarity;

    UPROPERTY()
    int32 Price;

    UPROPERTY()
    int64 ListedAt;
};
