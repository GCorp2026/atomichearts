// Copyright 2026 Atomic Hearts Team

#pragma once

#include "CoreMinimal.h"
#include "EWeaponEnums.h"
#include "ExoticNameGenerator.generated.h"

/**
 * Procedural name generator for exotic weapons.
 * Format: "{Prefix} {BaseName} '{Nickname}'"
 * Uses seeded deterministic selection from curated name pools.
 */
UCLASS()
class ATOMICHEARTS_API UExoticNameGenerator : public UObject
{
    GENERATED_BODY()

public:
    /** Generate deterministic name from seed and weapon slot */
    UFUNCTION(BlueprintCallable, Category = "Weapon|Exotic|Name")
    static FString GenerateName(int32 Seed, EWeaponSlot Slot);

    /** Get prefix pool size */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic|Name")
    static int32 GetPrefixCount() { return 30; }

    /** Get nickname pool size */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic|Name")
    static int32 GetNicknameCount() { return 54; }

    /** Get base name for a weapon slot by index (0-9) */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic|Name")
    static FString GetBaseName(EWeaponSlot Slot, int32 Index);

    /** Get all base names for a slot */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic|Name")
    static TArray<FString> GetBaseNamesForSlot(EWeaponSlot Slot);

    /** Pick a random lore template */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic|Name")
    static FString GetLoreTemplate(int32 Index);

private:
    /** Get prefix by deterministic index */
    static FString GetPrefix(int32 Index);

    /** Get nickname by deterministic index */
    static FString GetNickname(int32 Index);

    /** Lore template count */
    static constexpr int32 LoreTemplateCount() { return 10; }
};
