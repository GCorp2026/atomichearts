// Copyright 2026 Atomic Hearts Team

#pragma once

#include "CoreMinimal.h"
#include "EWeaponRarity.h"
#include "EWeaponSlot.h"
#include "EExoticTrait.generated.h"

/**
 * EExoticTraitCategories - groups for trait lookup by weapon type
 */
UENUM(BlueprintType)
enum class ETraitCategory : uint8
{
    Targeting,     // Homing, tracking, seeking
    FireMode,      // How the weapon fires
    Elemental,     // Damage over time / elemental
    Special,       // Unique mechanics
    Universal      // Works on any weapon type
};

/**
 * EExoticRarityTier - sub-tier within Exotic rarity
 */
UENUM(BlueprintType)
enum class EExoticRarityTier : uint8
{
    Common     = 0,   // 0-39:   40%  - 3 perks, 1 trait
    Rare       = 1,   // 40-74:  35%  - 4 perks, 1 trait
    Legendary  = 2,   // 75-94:  20%  - 4 perks, 1 signature
    Mythic     = 3    // 95-99:  5%   - 5 perks, 2 signatures
};
