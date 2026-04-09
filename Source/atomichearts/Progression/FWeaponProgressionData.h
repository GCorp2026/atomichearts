// Copyright 2026 Atomic Hearts Team
#pragma once
#include "CoreMinimal.h"
#include "EWeaponRarity.h"
#include "Weapons/FWeaponPerk.h"
#include "FWeaponProgressionData.generated.h"

/** XP required to reach each level. Level N requires XP[N-1] cumulative. */
USTRUCT(BlueprintType)
struct FWeaponProgressionData {
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 Level = 1;

    /** Cumulative XP needed to reach this level */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 XPRequired = 0;

    /** XP bonus to base stats at this level */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float DamageBonus = 0.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float FireRateBonus = 0.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float RangeBonus = 0.f;

    /** New perk unlocked at this level (if any) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FWeaponPerk UnlockedPerk;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    bool bHasUnlockedPerk = false;
};

/** Runtime state for a weapon's progression */
USTRUCT(BlueprintType)
struct FWeaponProgressionState {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentXP = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TotalKills = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Headshots = 0;

    /** Currently unlocked perks on this weapon */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FWeaponPerk> UnlockedPerks;

    /** Rarity upgrade path: starts at base rarity, can upgrade */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EWeaponRarity CurrentRarity = EWeaponRarity::Common;

    /** XP multipliers by source type */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float KillXPMultiplier = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HeadshotXPMultiplier = 2.0f;
};

USTRUCT(BlueprintType)
struct FRarityUpgradePath {
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    EWeaponRarity FromRarity = EWeaponRarity::Common;

    UPROPERTY(EditDefaultsOnly)
    EWeaponRarity ToRarity = EWeaponRarity::Uncommon;

    /** XP cost to perform this upgrade */
    UPROPERTY(EditDefaultsOnly)
    int32 UpgradeXP = 5000;

    /** Bonus stats granted on upgrade */
    UPROPERTY(EditDefaultsOnly)
    float DamageBonus = 10.f;

    UPROPERTY(EditDefaultsOnly)
    float FireRateBonus = 0.05f;
};
