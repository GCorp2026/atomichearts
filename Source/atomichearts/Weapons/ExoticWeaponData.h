// Copyright 2026 Atomic Hearts Team

#pragma once

#include "CoreMinimal.h"
#include "EWeaponEnums.h"
#include "AtomicheartsWeaponTypes.h"
#include "FWeaponPerk.h"
#include "FWeaponGeneratorResult.h"
#include "ExoticWeaponData.generated.h"

class UDataTable;

/**
 * Signature trait data for display and gameplay assignment
 */
USTRUCT(BlueprintType)
struct FExoticTraitData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString TraitName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ETraitCategory Category = ETraitCategory::Special;

    /** Which weapon slots this trait can appear on */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<EWeaponSlot> ValidSlots;

    /** Icon color for UI */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor TraitColor = FLinearColor::White;

    FExoticTraitData() {}
    FExoticTraitData(FString InName, FString InDesc, ETraitCategory InCat, TArray<EWeaponSlot> InSlots)
        : TraitName(InName), Description(InDesc), Category(InCat), ValidSlots(InSlots)
    {
        switch (InCat)
        {
        case ETraitCategory::Targeting:   TraitColor = FLinearColor(0.2f, 0.8f, 1.0f, 1.0f); break;
        case ETraitCategory::FireMode:    TraitColor = FLinearColor(1.0f, 0.5f, 0.2f, 1.0f); break;
        case ETraitCategory::Elemental:   TraitColor = FLinearColor(1.0f, 0.8f, 0.1f, 1.0f); break;
        case ETraitCategory::Special:     TraitColor = FLinearColor(0.8f, 0.2f, 1.0f, 1.0f); break;
        case ETraitCategory::Universal:  TraitColor = FLinearColor(0.6f, 0.6f, 0.6f, 1.0f); break;
        }
    }
};

/**
 * Lore template structure for procedural lore generation
 */
USTRUCT(BlueprintType)
struct FLoreTemplate
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString TemplateText;

    /** Weight for random selection (higher = more likely) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Weight = 1.0f;

    FLoreTemplate() {}
    FLoreTemplate(FString InText, float InWeight) : TemplateText(InText), Weight(InWeight) {}
};

/**
 * Extended stats for Exotic-tier weapons.
 * Inherits Damage, FireRate, Range, Accuracy, HeadshotMultiplier, LegshotMultiplier,
 * MaxRange, CriticalChance, CriticalMultiplier from FWeaponStats.
 */
USTRUCT(BlueprintType)
struct FExoticStats : public FWeaponStats
{
    GENERATED_BODY()

    /** Bonus armor penetration (0-1) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ArmorPiercing = 0.0f;

    /** Weapon handling score (0-1) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Handling = 0.75f;

    /** Reload speed score (0-1) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ReloadSpeed = 0.8f;

    FExoticStats() {}
    FExoticStats(const FWeaponStats& Base) : FWeaponStats(Base) {}
};

/**
 * Result struct for generated Exotic weapons
 * Full description of a single procedurally-generated exotic
 */
USTRUCT(BlueprintType)
struct FExoticWeaponData
{
    GENERATED_BODY()

    // --- Identity ---
    UPROPERTY()
    int32 ExoticIndex = 0;

    UPROPERTY()
    EWeaponSlot Slot = EWeaponSlot::Primary_AR;

    /** Full generated name: "{Prefix} {Base} '{Nickname}'" */
    UPROPERTY()
    FString Name;

    /** Lore text procedurally generated from templates */
    UPROPERTY()
    FString Lore;

    // --- Signatures ---
    UPROPERTY()
    EExoticTrait PrimaryTrait = EExoticTrait::None;

    UPROPERTY()
    FString PrimaryTraitName;

    /** Only Mythic tier weapons get a second signature trait */
    UPROPERTY()
    EExoticTrait SecondaryTrait = EExoticTrait::None;

    UPROPERTY()
    FString SecondaryTraitName;

    // --- Rarity & Tier ---
    UPROPERTY()
    EWeaponRarity Rarity = EWeaponRarity::Exotic;

    UPROPERTY()
    EExoticRarityTier Tier = EExoticRarityTier::Common;

    // --- Stats & Perks ---
    UPROPERTY()
    FExoticStats Stats;

    UPROPERTY()
    TArray<FWeaponPerk> Perks;

    // --- Visual ---
    /** Neon color for glow VFX and UI border */
    UPROPERTY()
    FLinearColor NeonColor = FLinearColor::White;

    /** Model variant index (0-3) for mesh variation */
    UPROPERTY()
    int32 ModelVariant = 0;

    // --- Blockchain ---
    /** Unique identifier for NFT/trading systems */
    UPROPERTY()
    FGuid BlockchainID;

    // --- Computed ---
    /** Human-readable tier name */
    UPROPERTY()
    FString TierName;

    FExoticWeaponData()
    {
        BlockchainID = FGuid::NewGuid();
    }

    FString GetDisplayName() const { return Name; }
    FString GetUniqueID() const { return FString::Printf(TEXT("EXOTIC_%03d_%s"), ExoticIndex, *UEnum::GetValueAsString(Slot)); }
};
