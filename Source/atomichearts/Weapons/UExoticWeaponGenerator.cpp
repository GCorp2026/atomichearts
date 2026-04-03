// Copyright Epic Games, Inc. All Rights Reserved.

#include "Weapons/UExoticWeaponGenerator.h"
#include "Weapons/FWeaponStats.h"
#include "Weapons/FWeaponPerk.h"
#include "Weapons/EExoticTrait.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/Crc.h"

FExoticWeaponResult UExoticWeaponGenerator::GenerateExotic(int32 Index, EWeaponSlot Slot)
{
    // Clamp to valid range and use seed from index for deterministic generation
    Index = FMath::Clamp(Index, 0, 99);
    
    const int32 SlotSeed = static_cast<int32>(Slot) * 100;
    FRandomStream Stream = CreateSeededStream(Index, SlotSeed);
    
    FExoticWeaponResult Result;
    Result.ExoticIndex = Index;
    Result.Slot = Slot;
    Result.Rarity = EWeaponRarity::Exotic;

    // Generate name deterministically from ExoticIndex
    Result.WeaponName = GenerateExoticName(Index, Slot);
    Result.UniqueID = FString::Printf(TEXT("EXOTIC_%d_%s"), Index, *UEnum::GetValueAsString(Slot));

    // Assign signature trait based on index (50 unique traits, cycling through 100 exotics)
    Result.SignatureTrait = GetSignatureTrait(Index % 50);
    Result.SignatureTraitName = GetTraitName(Result.SignatureTrait);

    // Generate stats based on tier (index determines tier: 0-24=base, 25-49=enhanced, 50-74=elite, 75-99=legendary)
    GenerateExoticStats(Result.Stats, Index, Stream);

    // Generate 5 perks deterministically
    GenerateExoticPerks(Result.Perks, Index, Stream);

    // Generate lore
    Result.LoreEntry = GenerateLore(Index, Result.WeaponName, Result.SignatureTrait);

    // Gold border for Exotic
    Result.BorderColor = FLinearColor(1.0f, 0.84f, 0.0f, 1.0f);

    return Result;
}

FExoticWeaponResult UExoticWeaponGenerator::GenerateRandomExotic(EWeaponSlot Slot)
{
    const int32 RandomIndex = FMath::RandRange(0, 99);
    return GenerateExotic(RandomIndex, Slot);
}

void UExoticWeaponGenerator::GenerateExoticStats(FWeaponStats& Stats, int32 Index, FRandomStream& Stream)
{
    // Tier determined by index: 0-24=base, 25-49=enhanced, 50-74=elite, 75-99=legendary
    const int32 Tier = Index / 25; // 0=base, 1=enhanced, 2=elite, 3=legendary
    const float TierMultiplier = 1.0f + (Tier * 0.3f); // 1.0, 1.3, 1.6, 1.9

    // Base damage ranges by slot category (approximated - actual weapon would come from slot)
    const float BaseDamage = 35.0f + Stream.FRand() * 25.0f;
    Stats.Damage = BaseDamage * TierMultiplier;

    // Critical stats improve with tier
    Stats.CriticalChance = 0.15f + Stream.FRand() * 0.35f + (Tier * 0.05f);
    Stats.CriticalMultiplier = 1.5f + Stream.FRand() * 1.0f + (Tier * 0.25f);

    // Range
    Stats.Range = 800.0f + Stream.FRand() * 1200.0f + (Tier * 200.0f);
    Stats.MaxRange = Stats.Range * 2.0f;

    // Accuracy improves with tier
    Stats.Accuracy = 0.72f + Stream.FRand() * 0.25f + (Tier * 0.02f);
    Stats.Accuracy = FMath::Clamp(Stats.Accuracy, 0.0f, 1.0f);

    // Headshot multiplier
    Stats.HeadshotMultiplier = 2.0f + (Tier * 0.15f);
    Stats.LegshotMultiplier = 0.5f;

    // Fire rate varies by tier
    Stats.FireRate = Tier == 0 ? (0.1f + Stream.FRand() * 0.4f) : (0.08f + Stream.FRand() * 0.5f);
}

void UExoticWeaponGenerator::GenerateExoticPerks(TArray<FWeaponPerk>& Perks, int32 Index, FRandomStream& Stream)
{
    // All exotics get exactly 5 perks
    static const TArray<FString> PerkNames = {
        "Rampage", "Kill Clip", "Multi-Kill Clip", "Quickdraw", "Snapshot",
        "Auto-Loading", "Incendiary Rounds", "Cryo Rounds", "Shock Rounds", "Void Burst",
        "Explosive Payload", "Cluster Bomb", "Firefly", "Dragonfly", "Air Assault",
        "High Impact", "Lightweight", "Heavy Guard", "Counter Balance", "Zen Moment",
        "Trench Barrel", "Field Prep", "Rapid Hit", "Outlaw", "Killower",
        "Vorpal Weapon", "Desperado", "Firing Line", "Adrenaline Junkie", "Swashbuckler",
        "Multikill Clip", "Eye of the Storm", "Grave Robber", "Feeding Frenzy", "Perpetual Motion",
        "Threat Detector", "Well of Ion", "Well of Radiance", "Archers Tempo", "Box Breathing",
        "No Distractions", "Steady Rounds", "Tactical Mag", "Alloy Casing", "Extended Barrel",
        "Corkscrew Ranging", "Full Bore", "Arrowhead Brake", "Flared Magwell", "Backup Mag"
    };

    static const TArray<FLinearColor> PerkColors = {
        FLinearColor(1.f, 0.3f, 0.3f),
        FLinearColor(0.3f, 1.f, 0.3f),
        FLinearColor(1.f, 0.8f, 0.2f),
        FLinearColor(0.5f, 0.5f, 1.f),
        FLinearColor(0.7f, 0.3f, 1.f)
    };

    // Deterministic perk selection: each exotic gets 5 unique perks based on index
    for (int32 i = 0; i < 5; ++i)
    {
        // Combine index and slot seed for variety across slots
        const int32 PerkSeed = Index * 5 + i;
        const int32 PerkIdx = PerkSeed % PerkNames.Num();

        FWeaponPerk Perk;
        Perk.PerkName = PerkNames[PerkIdx];
        Perk.Description = FString::Printf(TEXT("Exotic perk %d"), i + 1);
        
        // Rank cycles I, II, III based on index
        Perk.PerkRank = (PerkSeed % 3) + 1;
        
        // Color from our palette
        Perk.PerkColor = PerkColors[i % PerkColors.Num()];
        
        Perks.Add(Perk);
    }
}

FString UExoticWeaponGenerator::GetWeaponBaseName(EWeaponSlot Slot)
{
    switch (Slot)
    {
        case EWeaponSlot::Primary_AR:   return TEXT("Assault Rifle");
        case EWeaponSlot::Primary_PR:   return TEXT("Pulse Rifle");
        case EWeaponSlot::Primary_SR:   return TEXT("Scout Rifle");
        case EWeaponSlot::Secondary_HC: return TEXT("Hand Cannon");
        case EWeaponSlot::Secondary_SMG: return TEXT("Submachine Gun");
        case EWeaponSlot::Secondary_SG: return TEXT("Shotgun");
        case EWeaponSlot::Heavy_RL:     return TEXT("Rocket Launcher");
        case EWeaponSlot::Heavy_LMG:    return TEXT("Machine Gun");
        case EWeaponSlot::Heavy_SW:     return TEXT("Sword");
        case EWeaponSlot::Heavy_GL:     return TEXT("Grenade Launcher");
        default:                        return TEXT("Weapon");
    }
}

EExoticTrait UExoticWeaponGenerator::GetSignatureTrait(int32 Index)
{
    // 50 unique exotic traits, cycling based on index
    static const EExoticTrait Traits[] = {
        EExoticTrait::WolfpackRounds,
        EExoticTrait::TrackingSystem,
        EExoticTrait::SeekingProjectiles,
        EExoticTrait::LaserGuidance,
        EExoticTrait::SwarmMissiles,
        EExoticTrait::WallbangShot,
        EExoticTrait::HeadshotTracking,
        EExoticTrait::CorpseFinder,
        EExoticTrait::AOETracking,
        EExoticTrait::MultiLock,
        EExoticTrait::FullAutoConversion,
        EExoticTrait::BurstEnhancement,
        EExoticTrait::ChargeFire,
        EExoticTrait::SprayPray,
        EExoticTrait::DoubleFire,
        EExoticTrait::TripleFire,
        EExoticTrait::RapidFire,
        EExoticTrait::SlowMoFire,
        EExoticTrait::GravityFire,
        EExoticTrait::PlasmaFire,
        EExoticTrait::IncendiaryRounds,
        EExoticTrait::CryoRounds,
        EExoticTrait::ShockRounds,
        EExoticTrait::VoidRounds,
        EExoticTrait::SolarFlare,
        EExoticTrait::ArcPulse,
        EExoticTrait::StasisCrystal,
        EExoticTrait::StrandTangle,
        EExoticTrait::RadiationPoison,
        EExoticTrait::Antimatter,
        EExoticTrait::PortalShot,
        EExoticTrait::TimeDilate,
        EExoticTrait::ShieldPierce,
        EExoticTrait::PhaseWeapon,
        EExoticTrait::RicochetMaster,
        EExoticTrait::ExplosivePayload,
        EExoticTrait::ClusterBomb,
        EExoticTrait::FireAndForget,
        EExoticTrait::CombatRollReload,
        EExoticTrait::ThreatDetector,
        EExoticTrait::GhoulRounds,
        EExoticTrait::ExecutionerRounds,
        EExoticTrait::CascadeReactor,
        EExoticTrait::InfiniteAmmo,
        EExoticTrait::GravityHammer,
        EExoticTrait::SwordOnGun,
        EExoticTrait::RocketJump,
        EExoticTrait::TracerRound,
        EExoticTrait::MarkedDeath,
        EExoticTrait::SecondChance,
        EExoticTrait::Desperado,
        EExoticTrait::TrenchBarrel,
        EExoticTrait::AutoLoading,
        EExoticTrait::Quickdraw,
        EExoticTrait::Snapshot,
        EExoticTrait::FirmWare,
        EExoticTrait::NeuralLink,
        EExoticTrait::Guillotine
    };
    constexpr int32 TraitCount = 53;
    return Traits[Index % TraitCount];
}

FString UExoticWeaponGenerator::GetTraitName(EExoticTrait Trait)
{
    const UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EExoticTrait"), true);
    if (Enum)
    {
        return Enum->GetNameStringByValue(static_cast<int64>(Trait));
    }
    return TEXT("Unknown");
}

FString UExoticWeaponGenerator::GenerateLore(int32 Index, const FString& WeaponName, EExoticTrait Trait)
{
    const FString TraitStr = GetTraitName(Trait);
    const FString LoreTemplates[] = {
        TEXT("Forged in the chaos of the Corporate Wars, %s was wielded by the first Chrono-Soldiers."),
        TEXT("The prototype that started it all. %s has never failed its bearer."),
        TEXT("Hidden in the Neon Bunker for decades, %s now seeks a worthy wielder."),
        TEXT("Forged in the heart of a dying star, %s carries the essence of %s."),
        TEXT("Once wielded by a legendary guardian, %s channels %s with deadly precision."),
        TEXT(" whispers that %s was the last weapon fired before the Great Collapse."),
        TEXT("Field agents call %s \"The %s\" - a name earned through countless victories.")
    };
    const int32 TemplateIndex = Index % 7;
    if (TemplateIndex < 3)
    {
        // Templates 0-2 don't reference trait
        return FString::Printf(*LoreTemplates[TemplateIndex], *WeaponName);
    }
    return FString::Printf(*LoreTemplates[TemplateIndex], *WeaponName, *TraitStr);
}

FString UExoticWeaponGenerator::GenerateExoticName(int32 Index, EWeaponSlot Slot)
{
    // Prefix pool: mythological/legendary names
    const FString Prefixes[] = {
        "Mythoclast", "Praetorian", "Gungnir", "Mjolnir", "Excalibur",
        "Sphinx", "Hydra", "Phoenix", "SERPENT", "Behemoth",
        "Leviathan", "Chimera", "Minotaur", "Cerberus", "Argus",
        "Titan", "Colossus", "Cyclops", "Giant", "Dragon"
    };

    // Nickname pool: evocative titles
    const FString Nicknames[] = {
        "Wolfpack", "Desperado", "Havoc", "Rift", "Abyss",
        "Storm", "Thunder", "Fury", "Wrath", "Vengeance",
        "Judgment", "Destiny", "Fate", "Omen", "Herald",
        "Catalyst", "Nexus", "Apex", "Prime", "Omega",
        "Alpha", "Final"
    };

    const int32 PrefixIdx = Index % 20;
    const int32 NicknameIdx = (Index / 20) % 22;
    
    FString Base = GetWeaponBaseName(Slot);
    return FString::Printf(TEXT("%s %s '%s'"), *Prefixes[PrefixIdx], *Base, *Nicknames[NicknameIdx]);
}

FRandomStream UExoticWeaponGenerator::CreateSeededStream(int32 Index, int32 SlotSeed)
{
    const uint32 Hash = FCrc::MemCrc32(&Index, sizeof(int32));
    const uint32 Combined = Hash ^ FCrc::MemCrc32(&SlotSeed, sizeof(int32));
    return FRandomStream(Combined);
}
