// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/EWeaponEnums.h"
#include "Weapons/FWeaponGeneratorResult.h"
#include "Weapons/FWeaponStats.h"
#include "Weapons/FWeaponPerk.h"
#include "Weapons/EExoticTrait.h"
#include "FExoticWeaponResult.generated.h"

/**
 * Extended weapon generator result for Exotic weapons.
 * Includes signature trait and lore information.
 */
USTRUCT(BlueprintType)
struct ATOMICHEARTS_API FExoticWeaponResult
{
    GENERATED_BODY()

    // === Base WeaponGeneratorResult fields ===
    UPROPERTY() FString WeaponName;
    UPROPERTY() FString UniqueID;
    UPROPERTY() EWeaponSlot Slot;
    UPROPERTY() EWeaponRarity Rarity;
    UPROPERTY() FWeaponStats Stats;
    UPROPERTY() TArray<FWeaponPerk> Perks;
    UPROPERTY() FLinearColor BorderColor;
    
    // === Exotic-specific fields ===
    /** The signature trait that defines this exotic's unique behavior */
    UPROPERTY() EExoticTrait SignatureTrait;
    
    /** Human-readable name of the signature trait */
    UPROPERTY() FString SignatureTraitName;
    
    /** Lore entry describing the weapon's history/flavor */
    UPROPERTY() FString LoreEntry;
    
    /** Deterministic index 0-99 for this exotic within its weapon slot */
    UPROPERTY() int32 ExoticIndex;

    FExoticWeaponResult()
        : Slot(EWeaponSlot::Primary)
        , Rarity(EWeaponRarity::Exotic)
        , SignatureTrait(EExoticTrait::None)
        , ExoticIndex(0)
    {
        BorderColor = FLinearColor(1.0f, 0.84f, 0.0f, 1.0f); // Gold
    }
};
