// Copyright 2026 Atomic Hearts Team

#pragma once

#include "CoreMinimal.h"
#include "EWeaponEnums.h"
#include "ExoticWeaponData.h"
#include "ExoticWeaponGenerator.generated.h"

/**
 * UExoticWeaponGenerator - Procedural generator for 1000 Exotic weapons.
 *
 * 10 Weapon Classes × 100 Exotics = 1000 Total
 * All generation is deterministic (seeded) for reproducibility.
 *
 * Rarity distribution per 100:
 *   Common    (0-39):   40%   - 3 perks, 1 trait
 *   Rare      (40-74):  35%   - 4 perks, 1 trait
 *   Legendary (75-94):  20%   - 4 perks, 1 signature
 *   Mythic    (95-99):   5%   - 5 perks, 2 signatures
 */
UCLASS(BlueprintType)
class ATOMICHEARTS_API UExoticWeaponGenerator : public UObject
{
    GENERATED_BODY()

public:
    UExoticWeaponGenerator();

    /**
     * Generate a deterministic exotic weapon by index (0-99).
     * Same index + slot always produces the same exotic.
     */
    UFUNCTION(BlueprintCallable, Category = "Weapon|Exotic")
    static FExoticWeaponData GenerateExotic(int32 ExoticIndex, EWeaponSlot Slot);

    /**
     * Generate a random exotic for the given weapon slot.
     */
    UFUNCTION(BlueprintCallable, Category = "Weapon|Exotic")
    static FExoticWeaponData GenerateRandomExotic(EWeaponSlot Slot);

    /**
     * Generate a batch of N exotics for a slot (0 to N-1).
     */
    UFUNCTION(BlueprintCallable, Category = "Weapon|Exotic")
    static TArray<FExoticWeaponData> GenerateExoticBatch(EWeaponSlot Slot, int32 Count);

    /**
     * Get pool size per weapon slot.
     */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic")
    static int32 GetPoolSize() { return 100; }

    /**
     * Get total exotic count across all slots.
     */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic")
    static int32 GetTotalExoticCount() { return 1000; }

    /**
     * Get all weapon slots that can have exotic weapons.
     */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic")
    static TArray<EWeaponSlot> GetAllExoticSlots();

    // ---- Internal helpers (also callable) ----

    /** Pick rarity tier based on exotic index (0-99) */
    UFUNCTION(BlueprintCallable, Category = "Weapon|Exotic|Internal")
    static EExoticRarityTier IndexToTier(int32 ExoticIndex);

    /** Neon color for a given tier */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic|Internal")
    static FLinearColor GetTierColor(EExoticRarityTier Tier);

    /** Border/glow color for a given rarity */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic|Internal")
    static FLinearColor GetRarityColor(EWeaponRarity Rarity);

private:
    /** Create a seeded random stream for deterministic generation */
    static FRandomStream CreateSeededStream(int32 ExoticIndex, int32 SlotValue);

    /** Compute the master seed for generation */
    static int32 ComputeSeed(int32 ExoticIndex, EWeaponSlot Slot);

    /** Pick 1-2 signature traits based on exotic index and slot */
    static void PickSignatureTraits(int32 Seed, EWeaponSlot Slot, int32 ExoticIndex,
        EExoticTrait& OutPrimary, EExoticTrait& OutSecondary, int32& OutTraitCount);

    /** Generate lore text procedurally */
    static FString GenerateLoreText(int32 Seed, const FString& WeaponName,
        const FString& PrimaryTraitName, int32 ExoticIndex);

    /** Generate perks based on tier and seed */
    static void GeneratePerks(TArray<FWeaponPerk>& OutPerks, int32 Seed,
        EExoticRarityTier Tier, FRandomStream& Stream);

    /** Generate exotic-tier stats */
    static void GenerateStats(FExoticStats& OutStats, int32 Seed,
        EWeaponSlot Slot, EExoticRarityTier Tier, FRandomStream& Stream);

    /** Get the base weapon type string for a slot */
    static FString GetWeaponBaseType(EWeaponSlot Slot);

    /** Lore template constants */
    static constexpr int32 LoreTemplateCount() { return 10; }
    static constexpr int32 LoreYearBase() { return 2087; }
    static constexpr int32 LoreVictoryBase() { return 142; }
};
