// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/EWeaponEnums.h"
#include "Weapons/FExoticWeaponResult.h"
#include "UExoticWeaponGenerator.generated.h"

/**
 * Generator for Exotic weapons with deterministic exotic index (0-99).
 * Each exotic has a unique signature trait and lore entry.
 */
UCLASS()
class ATOMICHEARTS_API UExoticWeaponGenerator : public UObject
{
    GENERATED_BODY()

public:
    /** Generate a deterministic exotic weapon by index (0-99) */
    UFUNCTION(BlueprintCallable, Category = "Weapon|Exotic")
    static FExoticWeaponResult GenerateExotic(int32 Index, EWeaponSlot Slot);

    /** Generate a random exotic weapon for the given slot */
    UFUNCTION(BlueprintCallable, Category = "Weapon|Exotic")
    static FExoticWeaponResult GenerateRandomExotic(EWeaponSlot Slot);

    /** Get the total number of unique exotics per slot */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic")
    static int32 GetExoticPoolSize() { return 100; }

    /** Get trait name from enum */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic")
    static FString GetTraitName(EExoticTrait Trait);

private:
    /** Internal: Get signature trait for a given exotic index */
    static EExoticTrait GetSignatureTrait(int32 Index);

    /** Internal: Generate lore entry for an exotic */
    static FString GenerateLore(int32 Index, const FString& WeaponName, EExoticTrait Trait);

    /** Internal: Generate exotic weapon name */
    static FString GenerateExoticName(int32 Index, EWeaponSlot Slot);

    /** Internal: Seeded random for deterministic generation */
    static FRandomStream CreateSeededStream(int32 Index, int32 SlotSeed);

    /** Internal: Generate exotic-tier stats based on index (tier by index range) */
    static void GenerateExoticStats(FWeaponStats& Stats, int32 Index, FRandomStream& Stream);

    /** Internal: Generate 5 deterministic perks based on exotic index */
    static void GenerateExoticPerks(TArray<FWeaponPerk>& Perks, int32 Index, FRandomStream& Stream);

    /** Internal: Get the base weapon type name for a slot */
    static FString GetWeaponBaseName(EWeaponSlot Slot);
};
