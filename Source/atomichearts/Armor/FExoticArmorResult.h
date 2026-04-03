// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "EArmorSlot.h"
#include "EArmorRarity.h"
#include "EClassType.h"
#include "FArmorStats.h"
#include "EExoticIntrinsic.h"
#include "FExoticArmorResult.generated.h"

/**
 * Result structure for generated exotic armor pieces
 */
USTRUCT(BlueprintType)
struct FExoticArmorResult {
    GENERATED_BODY()

    UPROPERTY()
    FString ArmorName;

    UPROPERTY()
    FString UniqueID;

    UPROPERTY()
    EArmorSlot Slot;

    UPROPERTY()
    EClassType ClassType;

    UPROPERTY()
    EArmorRarity Rarity;

    UPROPERTY()
    FArmorStats Stats;

    UPROPERTY()
    TArray<FString> Perks;

    UPROPERTY()
    EExoticIntrinsic Intrinsic;

    UPROPERTY()
    FString IntrinsicName;

    UPROPERTY()
    FString LoreEntry;

    UPROPERTY()
    FLinearColor BorderColor;

    UPROPERTY()
    int32 ExoticIndex; // 0-9 per class

    FExoticArmorResult()
        : Slot(EArmorSlot::Helmet)
        , Rarity(EArmorRarity::Exotic)
        , Intrinsic(EExoticIntrinsic::None)
        , ExoticIndex(0)
        , BorderColor(FLinearColor(1.f, 0.8f, 0.f, 1.f))
    {}
};
