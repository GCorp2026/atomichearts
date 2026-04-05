// Copyright 2026 Atomic Hearts Team

#include "Weapons/ExoticWeaponGenerator.h"
#include "Weapons/ExoticNameGenerator.h"
#include "Weapons/ExoticTraitDatabase.h"
#include "Weapons/FWeaponPerk.h"
#include "Weapons/EExoticTrait.h"
#include "Weapons/EWeaponSlot.h"
#include "Weapons/EWeaponRarity.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/Crc.h"

UExoticWeaponGenerator::UExoticWeaponGenerator() {}

// ============================================================
// PUBLIC API
// ============================================================

FExoticWeaponData UExoticWeaponGenerator::GenerateExotic(int32 ExoticIndex, EWeaponSlot Slot)
{
    // Clamp index to valid range
    ExoticIndex = FMath::Clamp(ExoticIndex, 0, 99);
    const int32 Seed = ComputeSeed(ExoticIndex, Slot);
    FRandomStream Stream = CreateSeededStream(ExoticIndex, static_cast<int32>(Slot));

    FExoticWeaponData Data;
    Data.ExoticIndex = ExoticIndex;
    Data.Slot = Slot;

    // --- Tier & Rarity ---
    Data.Tier = IndexToTier(ExoticIndex);
    Data.Rarity = EWeaponRarity::Exotic;
    Data.NeonColor = GetTierColor(Data.Tier);

    // Tier display name
    switch (Data.Tier)
    {
    case EExoticRarityTier::Common:    Data.TierName = TEXT("Common Exotic");    break;
    case EExoticRarityTier::Rare:      Data.TierName = TEXT("Rare Exotic");     break;
    case EExoticRarityTier::Legendary: Data.TierName = TEXT("Legendary Exotic"); break;
    case EExoticRarityTier::Mythic:    Data.TierName = TEXT("Mythic Exotic");    break;
    }

    // --- Name ---
    Data.Name = UExoticNameGenerator::GenerateName(Seed, Slot);

    // --- Signature Traits ---
    int32 TraitCount = 1;
    PickSignatureTraits(Seed, Slot, ExoticIndex,
        Data.PrimaryTrait, Data.SecondaryTrait, TraitCount);

    Data.PrimaryTraitName = UExoticTraitDatabase::GetTraitName(Data.PrimaryTrait);
    if (Data.SecondaryTrait != EExoticTrait::None)
        Data.SecondaryTraitName = UExoticTraitDatabase::GetTraitName(Data.SecondaryTrait);

    // --- Stats ---
    GenerateStats(Data.Stats, Seed, Slot, Data.Tier, Stream);

    // --- Perks ---
    GeneratePerks(Data.Perks, Seed, Data.Tier, Stream);

    // --- Lore ---
    Data.Lore = GenerateLoreText(Seed, Data.Name, Data.PrimaryTraitName, ExoticIndex);

    // --- Visual ---
    Data.ModelVariant = ExoticIndex % 4;

    // --- Blockchain ID (deterministic from seed) ---
    Data.BlockchainID = FGuid(Seed, Seed >> 16, Seed >> 8, Seed);

    return Data;
}

FExoticWeaponData UExoticWeaponGenerator::GenerateRandomExotic(EWeaponSlot Slot)
{
    const int32 RandomIndex = FMath::RandRange(0, 99);
    return GenerateExotic(RandomIndex, Slot);
}

TArray<FExoticWeaponData> UExoticWeaponGenerator::GenerateExoticBatch(EWeaponSlot Slot, int32 Count)
{
    TArray<FExoticWeaponData> Results;
    Results.Reserve(Count);
    for (int32 i = 0; i < Count; ++i)
        Results.Add(GenerateExotic(i, Slot));
    return Results;
}

TArray<EWeaponSlot> UExoticWeaponGenerator::GetAllExoticSlots()
{
    return TArray<EWeaponSlot>{
        EWeaponSlot::Primary_AR, EWeaponSlot::Primary_PR, EWeaponSlot::Primary_SR,
        EWeaponSlot::Secondary_HC, EWeaponSlot::Secondary_SMG, EWeaponSlot::Secondary_SG,
        EWeaponSlot::Heavy_RL, EWeaponSlot::Heavy_LMG, EWeaponSlot::Heavy_SW, EWeaponSlot::Heavy_GL
    };
}

// ============================================================
// TIER & COLOR
// ============================================================

EExoticRarityTier UExoticWeaponGenerator::IndexToTier(int32 ExoticIndex)
{
    if (ExoticIndex >= 95) return EExoticRarityTier::Mythic;
    if (ExoticIndex >= 75) return EExoticRarityTier::Legendary;
    if (ExoticIndex >= 40) return EExoticRarityTier::Rare;
    return EExoticRarityTier::Common;
}

FLinearColor UExoticWeaponGenerator::GetTierColor(EExoticRarityTier Tier)
{
    switch (Tier)
    {
    case EExoticRarityTier::Common:    return FLinearColor(0.9f, 0.9f, 0.9f, 1.0f); // White
    case EExoticRarityTier::Rare:      return FLinearColor(0.3f, 0.5f, 1.0f, 1.0f); // Blue
    case EExoticRarityTier::Legendary: return FLinearColor(0.8f, 0.2f, 1.0f, 1.0f); // Purple
    case EExoticRarityTier::Mythic:    return FLinearColor(1.0f, 0.85f, 0.0f, 1.0f); // Gold
    default: return FLinearColor::White;
    }
}

FLinearColor UExoticWeaponGenerator::GetRarityColor(EWeaponRarity Rarity)
{
    switch (Rarity)
    {
    case EWeaponRarity::Common:    return FLinearColor(0.8f, 0.8f, 0.8f, 1.0f);
    case EWeaponRarity::Uncommon:  return FLinearColor(0.2f, 0.8f, 0.2f, 1.0f);
    case EWeaponRarity::Rare:      return FLinearColor(0.2f, 0.4f, 1.0f, 1.0f);
    case EWeaponRarity::Legendary: return FLinearColor(1.0f, 0.5f, 0.0f, 1.0f);
    case EWeaponRarity::Exotic:    return FLinearColor(1.0f, 0.84f, 0.0f, 1.0f); // Gold
    default: return FLinearColor::White;
    }
}

// ============================================================
// SEED & STREAMS
// ============================================================

int32 UExoticWeaponGenerator::ComputeSeed(int32 ExoticIndex, EWeaponSlot Slot)
{
    // Combine ExoticIndex, Slot, and SeasonNumber into a single seed
    // Season number: hardcoded to season 1 for now (could be configurable)
    constexpr int32 SeasonNumber = 1;
    const int32 SlotVal = static_cast<int32>(Slot);

    // FNV-1a style combine
    uint32 Hash = 2166136261u;
    uint32 Data[] = { static_cast<uint32>(ExoticIndex), static_cast<uint32>(SlotVal),
                      static_cast<uint32>(SeasonNumber) };
    for (int32 i = 0; i < 3; ++i)
    {
        Hash ^= Data[i];
        Hash *= 16777619u;
    }
    return static_cast<int32>(Hash);
}

FRandomStream UExoticWeaponGenerator::CreateSeededStream(int32 ExoticIndex, int32 SlotValue)
{
    const int32 Combined = ComputeSeed(ExoticIndex, static_cast<EWeaponSlot>(SlotValue));
    return FRandomStream(FCrc::MemCrc32(&Combined, sizeof(int32)));
}

// ============================================================
// TRAIT SELECTION
// ============================================================

void UExoticWeaponGenerator::PickSignatureTraits(int32 Seed, EWeaponSlot Slot,
    int32 ExoticIndex, EExoticTrait& OutPrimary, EExoticTrait& OutSecondary,
    int32& OutTraitCount)
{
    TArray<FExoticTraitData> ValidTraits = UExoticTraitDatabase::GetTraitsForSlot(Slot);
    if (ValidTraits.IsEmpty())
    {
        OutPrimary = EExoticTrait::None;
        OutSecondary = EExoticTrait::None;
        OutTraitCount = 0;
        return;
    }

    const EExoticRarityTier Tier = IndexToTier(ExoticIndex);
    OutTraitCount = (Tier == EExoticRarityTier::Mythic) ? 2 : 1;

    // Deterministic primary trait selection
    const int32 PrimaryIdx = Seed % ValidTraits.Num();
    OutPrimary = ValidTraits[PrimaryIdx].TraitName.Len() > 0
        ? static_cast<EExoticTrait>(PrimaryIdx) : EExoticTrait::None;

    // Secondary only for Mythic
    if (OutTraitCount == 2)
    {
        // Pick a different trait for secondary
        const int32 SecondarySeed = (Seed * 7) % ValidTraits.Num();
        OutSecondary = SecondarySeed != PrimaryIdx
            ? static_cast<EExoticTrait>(SecondarySeed) : EExoticTrait::None;
    }
    else
    {
        OutSecondary = EExoticTrait::None;
    }
}

// ============================================================
// LORE GENERATION
// ============================================================

FString UExoticWeaponGenerator::GenerateLoreText(int32 Seed, const FString& WeaponName,
    const FString& TraitName, int32 ExoticIndex)
{
    const int32 TemplateIdx = Seed % LoreTemplateCount();
    FString Template = UExoticNameGenerator::GetLoreTemplate(TemplateIdx);

    // Pull some seed-derived numbers for templates that need them
    const int32 Year = LoreYearBase() + (Seed % 100);
    const int32 Victories = LoreVictoryBase() + (Seed % 500);

    switch (TemplateIdx)
    {
    case 0: case 1: case 2:
        return FString::Printf(*Template, *WeaponName);
    case 3: case 4:
        return FString::Printf(*Template, *WeaponName, *TraitName);
    case 5:
        return FString::Printf(*Template, *WeaponName);
    case 6:
        return FString::Printf(*Template, *WeaponName, *TraitName, Year, Victories);
    default:
        return FString::Printf(*Template, *WeaponName);
    }
}

// ============================================================
// PERK GENERATION
// ============================================================

void UExoticWeaponGenerator::GeneratePerks(TArray<FWeaponPerk>& OutPerks, int32 Seed,
    EExoticRarityTier Tier, FRandomStream& Stream)
{
    OutPerks.Reset();

    // Perk count by tier
    int32 PerkCount = 3;
    switch (Tier)
    {
    case EExoticRarityTier::Common:    PerkCount = 3; break;
    case EExoticRarityTier::Rare:       PerkCount = 4; break;
    case EExoticRarityTier::Legendary:  PerkCount = 4; break;
    case EExoticRarityTier::Mythic:    PerkCount = 5; break;
    }

    // Perk pool (60 perks for variety)
    const TArray<FString> PerkNames = {
        "Rampage", "Kill Clip", "Multi-Kill Clip", "Quickdraw", "Snapshot",
        "Auto-Loading", "Incendiary Rounds", "Cryo Rounds", "Shock Rounds", "Void Burst",
        "Explosive Payload", "Cluster Bomb", "Firefly", "Dragonfly", "Air Assault",
        "High Impact", "Lightweight", "Heavy Guard", "Counter Balance", "Zen Moment",
        "Trench Barrel", "Field Prep", "Rapid Hit", "Outlaw", "Killower",
        "Vorpal Weapon", "Desperado", "Firing Line", "Adrenaline Junkie", "Swashbuckler",
        "Multikill Clip", "Eye of the Storm", "Grave Robber", "Feeding Frenzy", "Perpetual Motion",
        "Threat Detector", "Well of Ion", "Archers Tempo", "Box Breathing",
        "No Distractions", "Steady Rounds", "Tactical Mag", "Alloy Casing", "Extended Barrel",
        "Corkscrew Ranging", "Full Bore", "Arrowhead Brake", "Flared Magwell", "Backup Mag",
        "Subsistence", "Wellspring", "Headstone", "Elemental Capacitor", "Controlled Burst",
        "Sustained Damage", "Precision Instrument", "Eager Edge", "Energy Transfer", "Surge"
    };

    const TArray<FLinearColor> PerkColors = {
        FLinearColor(1.0f, 0.3f, 0.3f), FLinearColor(0.3f, 1.0f, 0.3f),
        FLinearColor(1.0f, 0.8f, 0.2f), FLinearColor(0.5f, 0.5f, 1.0f),
        FLinearColor(0.7f, 0.3f, 1.0f)
    };

    for (int32 i = 0; i < PerkCount; ++i)
    {
        const int32 PerkSeed = (Seed * 13 + i * 7) % PerkNames.Num();
        FWeaponPerk Perk;
        Perk.PerkName = PerkNames[PerkSeed];
        Perk.Description = FString::Printf(TEXT("Rank %d exotic perk"), (PerkSeed % 3) + 1);
        Perk.PerkRank = (PerkSeed % 3) + 1;
        Perk.PerkColor = PerkColors[i % PerkColors.Num()];
        OutPerks.Add(Perk);
    }
}

// ============================================================
// STAT GENERATION
// ============================================================

void UExoticWeaponGenerator::GenerateStats(FExoticStats& OutStats, int32 Seed,
    EWeaponSlot Slot, EExoticRarityTier Tier, FRandomStream& Stream)
{
    // Tier multiplier for scaling
    const float TierMult = 1.0f + static_cast<float>(Tier) * 0.3f; // 1.0 / 1.3 / 1.6 / 1.9

    // Base damage by slot
    float BaseDamage = 35.0f;
    switch (Slot)
    {
    case EWeaponSlot::Secondary_SG: BaseDamage = 90.0f;  break;
    case EWeaponSlot::Heavy_RL:     BaseDamage = 200.0f; break;
    case EWeaponSlot::Heavy_GL:     BaseDamage = 150.0f; break;
    case EWeaponSlot::Heavy_LMG:     BaseDamage = 40.0f;  break;
    case EWeaponSlot::Heavy_SW:     BaseDamage = 120.0f; break;
    case EWeaponSlot::Secondary_HC: BaseDamage = 65.0f;  break;
    case EWeaponSlot::Primary_SR:   BaseDamage = 50.0f;  break;
    case EWeaponSlot::Primary_AR:   BaseDamage = 28.0f;  break;
    case EWeaponSlot::Primary_PR:   BaseDamage = 24.0f;  break;
    case EWeaponSlot::Secondary_SMG: BaseDamage = 20.0f;  break;
    default:                         BaseDamage = 30.0f;
    }
    OutStats.Damage = BaseDamage * TierMult * (0.85f + Stream.FRand() * 0.3f);

    // Critical stats
    OutStats.CriticalChance = FMath::Clamp(0.12f + Stream.FRand() * 0.35f + (Tier * 0.05f), 0.0f, 0.8f);
    OutStats.CriticalMultiplier = 1.5f + Stream.FRand() * 1.0f + (Tier * 0.25f);

    // Range
    OutStats.Range = 800.0f + Stream.FRand() * 1200.0f + (Tier * 200.0f);
    OutStats.MaxRange = OutStats.Range * 2.0f;

    // Accuracy
    OutStats.Accuracy = FMath::Clamp(0.72f + Stream.FRand() * 0.25f + (Tier * 0.02f), 0.5f, 1.0f);

    // Headshot / legshot
    OutStats.HeadshotMultiplier = 2.0f + (Tier * 0.15f);
    OutStats.LegshotMultiplier = 0.5f;

    // Fire rate (varies by slot category)
    if (Slot == EWeaponSlot::Heavy_RL || Slot == EWeaponSlot::Heavy_GL)
        OutStats.FireRate = 1.5f + Stream.FRand() * 0.5f; // Slow for explosives
    else if (Slot == EWeaponSlot::Secondary_SG || Slot == EWeaponSlot::Heavy_SW)
        OutStats.FireRate = 1.0f + Stream.FRand() * 0.8f; // Melee-ish
    else
        OutStats.FireRate = 0.08f + Stream.FRand() * 0.5f;

    // Handling & reload
    OutStats.Handling = FMath::Clamp(0.65f + Stream.FRand() * 0.35f, 0.0f, 1.0f);
    OutStats.ReloadSpeed = FMath::Clamp(0.7f + Stream.FRand() * 0.3f, 0.0f, 1.0f);
    OutStats.ArmorPiercing = 0.0f + (Tier * 0.1f) + Stream.FRand() * 0.3f;
}

FString UExoticWeaponGenerator::GetWeaponBaseType(EWeaponSlot Slot)
{
    switch (Slot)
    {
    case EWeaponSlot::Primary_AR:       return TEXT("Assault Rifle");
    case EWeaponSlot::Primary_PR:       return TEXT("Pulse Rifle");
    case EWeaponSlot::Primary_SR:       return TEXT("Scout Rifle");
    case EWeaponSlot::Secondary_HC:    return TEXT("Hand Cannon");
    case EWeaponSlot::Secondary_SMG:    return TEXT("Submachine Gun");
    case EWeaponSlot::Secondary_SG:     return TEXT("Shotgun");
    case EWeaponSlot::Heavy_RL:          return TEXT("Rocket Launcher");
    case EWeaponSlot::Heavy_LMG:         return TEXT("Machine Gun");
    case EWeaponSlot::Heavy_SW:          return TEXT("Sword");
    case EWeaponSlot::Heavy_GL:          return TEXT("Grenade Launcher");
    default:                            return TEXT("Weapon");
    }
}
