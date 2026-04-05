// Copyright 2026 Atomic Hearts Team

#include "Weapons/ExoticTraitDatabase.h"
#include "Weapons/EExoticTrait.h"
#include "Weapons/EWeaponSlot.h"

TMap<EExoticTrait, FExoticTraitData>& UExoticTraitDatabase::GetRegistry()
{
    static TMap<EExoticTrait, FExoticTraitData> Registry;
    return Registry;
}

void UExoticTraitDatabase::EnsureRegistryBuilt()
{
    TMap<EExoticTrait, FExoticTraitData>& Registry = GetRegistry();
    if (!Registry.IsEmpty()) return;

    // clang-format off
    auto AllSlots = TArray<EWeaponSlot>{
        EWeaponSlot::Primary_AR, EWeaponSlot::Primary_PR, EWeaponSlot::Primary_SR,
        EWeaponSlot::Secondary_HC, EWeaponSlot::Secondary_SMG, EWeaponSlot::Secondary_SG,
        EWeaponSlot::Heavy_RL, EWeaponSlot::Heavy_LMG, EWeaponSlot::Heavy_SW, EWeaponSlot::Heavy_GL
    };

    auto PrimarySlots = TArray<EWeaponSlot>{
        EWeaponSlot::Primary_AR, EWeaponSlot::Primary_PR, EWeaponSlot::Primary_SR,
        EWeaponSlot::Secondary_HC, EWeaponSlot::Secondary_SMG
    };

    auto HeavySlots = TArray<EWeaponSlot>{
        EWeaponSlot::Heavy_RL, EWeaponSlot::Heavy_LMG, EWeaponSlot::Heavy_SW, EWeaponSlot::Heavy_GL
    };

    auto PrecisionSlots = TArray<EWeaponSlot>{
        EWeaponSlot::Primary_SR, EWeaponSlot::Secondary_HC
    };

    auto CloseRangeSlots = TArray<EWeaponSlot>{
        EWeaponSlot::Primary_AR, EWeaponSlot::Secondary_SG, EWeaponSlot::Secondary_SMG
    };

    // ============================================================
    // TARGETING (10)
    // ============================================================
    Registry.Add(EExoticTrait::WolfpackRounds,    FExoticTraitData("Wolfpack Rounds",    "Projectiles spawn homing cluster bombs on impact that track nearby enemies",     ETraitCategory::Targeting,  AllSlots));
    Registry.Add(EExoticTrait::TrackingSystem,    FExoticTraitData("Tracking System",     "Auto-acquires and tracks the nearest enemy within line of sight",                ETraitCategory::Targeting,  AllSlots));
    Registry.Add(EExoticTrait::SeekingProjectiles,FExoticTraitData("Seeking Projectiles", "Projectiles curve toward enemies within proximity radius",                          ETraitCategory::Targeting,  AllSlots));
    Registry.Add(EExoticTrait::LaserGuidance,     FExoticTraitData("Laser Guidance",      "Laser-guided projectiles that follow the crosshair onto targets",                ETraitCategory::Targeting,  PrimarySlots));
    Registry.Add(EExoticTrait::SwarmMissiles,     FExoticTraitData("Swarm Missiles",       "Fires a volley of multiple tracking missiles",                                   ETraitCategory::Targeting,  HeavySlots));
    Registry.Add(EExoticTrait::WallbangShot,      FExoticTraitData("Wallbang Shot",        "Projectiles penetrate walls and obstacles to hit enemies behind cover",           ETraitCategory::Targeting,  AllSlots));
    Registry.Add(EExoticTrait::HeadshotTracking,  FExoticTraitData("Headshot Tracking",    "Projectiles snap to enemy head hitboxes for precision damage",                   ETraitCategory::Targeting,  PrecisionSlots));
    Registry.Add(EExoticTrait::CorpseFinder,      FExoticTraitData("Corpse Finder",         "Projectiles seek out and reanimate enemy corpses as combat drones",                 ETraitCategory::Targeting,  CloseRangeSlots));
    Registry.Add(EExoticTrait::AOETracking,       FExoticTraitData("AOE Tracking",          "Area-of-effect detonations follow moving targets",                                 ETraitCategory::Targeting,  HeavySlots));
    Registry.Add(EExoticTrait::MultiLock,         FExoticTraitData("Multi-Lock",            "Locks onto multiple targets simultaneously and fires at all marked enemies",       ETraitCategory::Targeting,  HeavySlots));

    // ============================================================
    // FIRE MODE (10)
    // ============================================================
    Registry.Add(EExoticTrait::FullAutoConversion, FExoticTraitData("Full Auto Conversion","Converts any weapon to aggressive full-auto with increased damage",             ETraitCategory::FireMode,   AllSlots));
    Registry.Add(EExoticTrait::BurstEnhancement,   FExoticTraitData("Burst Enhancement",   "Burst-fire weapons cycle faster with tighter spread",                             ETraitCategory::FireMode,   PrimarySlots));
    Registry.Add(EExoticTrait::ChargeFire,         FExoticTraitData("Charge Fire",         "Hold to charge; release for a devastating overcharged shot",                       ETraitCategory::FireMode,   AllSlots));
    Registry.Add(EExoticTrait::SprayPray,          FExoticTraitData("Spray & Pray",         "Extreme spread with dramatically increased damage per hit",                       ETraitCategory::FireMode,   CloseRangeSlots));
    Registry.Add(EExoticTrait::DoubleFire,         FExoticTraitData("Double Fire",          "Fires two projectiles simultaneously per trigger pull",                          ETraitCategory::FireMode,   AllSlots));
    Registry.Add(EExoticTrait::TripleFire,         FExoticTraitData("Triple Fire",          "Fires three projectiles simultaneously in a spread pattern",                       ETraitCategory::FireMode,   PrimarySlots));
    Registry.Add(EExoticTrait::RapidFire,          FExoticTraitData("Rapid Fire",           "Massive fire rate increase with slight damage reduction",                         ETraitCategory::FireMode,   AllSlots));
    Registry.Add(EExoticTrait::SlowMoFire,         FExoticTraitData("Slow-Mo Fire",         "Projectiles travel and impact in bullet-time slow motion",                       ETraitCategory::FireMode,   PrecisionSlots));
    Registry.Add(EExoticTrait::GravityFire,        FExoticTraitData("Gravity Fire",         "Projectiles generate a gravity pull that drags enemies toward impact point",    ETraitCategory::FireMode,   HeavySlots));
    Registry.Add(EExoticTrait::PlasmaFire,         FExoticTraitData("Plasma Fire",          "Converts projectiles to superheated plasma with bonus burn damage",             ETraitCategory::FireMode,   AllSlots));

    // ============================================================
    // ELEMENTAL (10)
    // ============================================================
    Registry.Add(EExoticTrait::IncendiaryRounds,  FExoticTraitData("Incendiary Rounds",    "Armor-piercing burn damage over time",                                          ETraitCategory::Elemental,  AllSlots));
    Registry.Add(EExoticTrait::CryoRounds,         FExoticTraitData("Cryo Rounds",           "Slows and can freeze enemies on sustained hit",                                  ETraitCategory::Elemental,  AllSlots));
    Registry.Add(EExoticTrait::ShockRounds,        FExoticTraitData("Shock Rounds",          "Chain lightning arcs between nearby enemies",                                    ETraitCategory::Elemental,  AllSlots));
    Registry.Add(EExoticTrait::VoidRounds,         FExoticTraitData("Void Rounds",            "Devour and weaken enemies on hit; kills grant health",                          ETraitCategory::Elemental,  AllSlots));
    Registry.Add(EExoticTrait::SolarFlare,         FExoticTraitData("Solar Flare",            "Explosive solar damage that ignites the surrounding area",                      ETraitCategory::Elemental,   HeavySlots));
    Registry.Add(EExoticTrait::ArcPulse,            FExoticTraitData("Arc Pulse",             "AoE arc pulse burst on every kill",                                             ETraitCategory::Elemental,  CloseRangeSlots));
    Registry.Add(EExoticTrait::StasisCrystal,       FExoticTraitData("Stasis Crystal",         "Shatters frozen enemies into stasis shards that damage nearby foes",             ETraitCategory::Elemental,  AllSlots));
    Registry.Add(EExoticTrait::StrandTangle,        FExoticTraitData("Strand Tangle",          "Suspends enemies in strand webs on hit; kills spread suspension",               ETraitCategory::Elemental,  AllSlots));
    Registry.Add(EExoticTrait::RadiationPoison,     FExoticTraitData("Radiation Poison",      "Radiation damage over time; stackable intensity",                               ETraitCategory::Elemental,  AllSlots));
    Registry.Add(EExoticTrait::Antimatter,          FExoticTraitData("Antimatter",             "Void antimatter explosions on impact that pull in nearby enemies",              ETraitCategory::Elemental,   HeavySlots));

    // ============================================================
    // SPECIAL (20)
    // ============================================================
    Registry.Add(EExoticTrait::PortalShot,         FExoticTraitData("Portal Shot",           "Projectiles create linked portals on impact for tactical repositioning",         ETraitCategory::Special,    PrecisionSlots));
    Registry.Add(EExoticTrait::TimeDilate,         FExoticTraitData("Time Dilate",            "Hit enemies move at reduced speed for a duration after being hit",              ETraitCategory::Special,    AllSlots));
    Registry.Add(EExoticTrait::ShieldPierce,      FExoticTraitData("Shield Pierce",          "Ignores all shield types and barriers; deals bonus damage to shields",          ETraitCategory::Special,    AllSlots));
    Registry.Add(EExoticTrait::PhaseWeapon,        FExoticTraitData("Phase Weapon",           "Projectiles pass through solid walls and obstacles",                             ETraitCategory::Special,    AllSlots));
    Registry.Add(EExoticTrait::RicochetMaster,     FExoticTraitData("Ricochet Master",        "Projectiles ricochet off surfaces up to 5 times",                               ETraitCategory::Special,    AllSlots));
    Registry.Add(EExoticTrait::ExplosivePayload,  FExoticTraitData("Explosive Payload",      "AoE explosion on every impact",                                                  ETraitCategory::Special,    HeavySlots));
    Registry.Add(EExoticTrait::ClusterBomb,        FExoticTraitData("Cluster Bomb",            "Projectiles split into multiple child bomblets on impact",                      ETraitCategory::Special,    HeavySlots));
    Registry.Add(EExoticTrait::FireAndForget,      FExoticTraitData("Fire And Forget",        "Weapon auto-targets and fires at nearby enemies after initial shot",            ETraitCategory::Special,    AllSlots));
    Registry.Add(EExoticTrait::CombatRollReload,  FExoticTraitData("Combat Roll Reload",     "Performing a dodge automatically reloads the weapon",                             ETraitCategory::Special,    AllSlots));
    Registry.Add(EExoticTrait::ThreatDetector,    FExoticTraitData("Threat Detector",         "Highlights enemy weak points and critical hit locations",                        ETraitCategory::Special,    AllSlots));
    Registry.Add(EExoticTrait::GhoulRounds,       FExoticTraitData("Ghoul Rounds",           "Bonus damage and healing on low-health enemy kills",                             ETraitCategory::Special,    CloseRangeSlots));
    Registry.Add(EExoticTrait::ExecutionerRounds, FExoticTraitData("Executioner Rounds",     "Massive bonus damage versus low-health targets",                                 ETraitCategory::Special,    PrecisionSlots));
    Registry.Add(EExoticTrait::CascadeReactor,     FExoticTraitData("Cascade Reactor",        "Kills trigger chain explosions that spread to nearby enemies",                  ETraitCategory::Special,    AllSlots));
    Registry.Add(EExoticTrait::InfiniteAmmo,      FExoticTraitData("Infinite Ammo",           "No reload required; regenerates ammo passively over time",                      ETraitCategory::Special,    AllSlots));
    Registry.Add(EExoticTrait::GravityHammer,       FExoticTraitData("Gravity Hammer",         "Melee slam creates a gravity well that pulls in and damages nearby enemies",    ETraitCategory::Special,    HeavySlots));
    Registry.Add(EExoticTrait::SwordOnGun,         FExoticTraitData("Sword On Gun",            "Bayonet melee attacks deal heavy damage and stagger",                            ETraitCategory::Special,    CloseRangeSlots));
    Registry.Add(EExoticTrait::RocketJump,        FExoticTraitData("Rocket Jump",             "Firing propels the player into the air; no self-damage",                        ETraitCategory::Special,    HeavySlots));
    Registry.Add(EExoticTrait::TracerRound,        FExoticTraitData("Tracer Round",            "Reveals enemy position and pathing to all allies",                               ETraitCategory::Special,    PrecisionSlots));
    Registry.Add(EExoticTrait::MarkedDeath,        FExoticTraitData("Marked Death",            "Marked enemies take increased damage from all sources",                          ETraitCategory::Special,    AllSlots));
    Registry.Add(EExoticTrait::SecondChance,       FExoticTraitData("Second Chance",           "Revive once per life on kill; cooldown resets on death",                        ETraitCategory::Special,    AllSlots));

    // ============================================================
    // ADDITIONAL EXOTIC PERKS (13 more - completing the 53 total)
    // ============================================================
    Registry.Add(EExoticTrait::Desperado,          FExoticTraitData("Desperado",               "Precision kills grant rapid fire rate boost",                                    ETraitCategory::Special,    PrimarySlots));
    Registry.Add(EExoticTrait::TrenchBarrel,       FExoticTraitData("Trench Barrel",           "Damage increases with consecutive hits, resets on reload",                       ETraitCategory::Special,    CloseRangeSlots));
    Registry.Add(EExoticTrait::AutoLoading,       FExoticTraitData("Auto-Loading",            "Weapon auto-loads while holstered",                                             ETraitCategory::Special,    AllSlots));
    Registry.Add(EExoticTrait::Quickdraw,         FExoticTraitData("Quickdraw",               "Instant swap and ADS readiness",                                                 ETraitCategory::Special,    AllSlots));
    Registry.Add(EExoticTrait::Snapshot,          FExoticTraitData("Snapshot",                 "Instant aim-down-sights from the hip",                                           ETraitCategory::Special,    PrecisionSlots));
    Registry.Add(EExoticTrait::FirmWare,           FExoticTraitData("Firm Ware",               "Weapon gains bonus stats and new mode after sustained fire",                    ETraitCategory::Special,    AllSlots));
    Registry.Add(EExoticTrait::NeuralLink,        FExoticTraitData("Neural Link",             "Creates combat markers; allied damage buffs against marked enemies",            ETraitCategory::Special,    AllSlots));
    Registry.Add(EExoticTrait::Guillotine,         FExoticTraitData("Guillotine",               "Heavy attack throws the weapon and returns like a boomerang",                    ETraitCategory::Special,    HeavySlots));
    Registry.Add(EExoticTrait::VorpalWeapon,      FExoticTraitData("Vorpal Weapon",           "Bonus damage versus boss and champion enemies",                                  ETraitCategory::Special,    PrecisionSlots));
    Registry.Add(EExoticTrait::BoxBreathing,      FExoticTraitData("Box Breathing",             "Sustained ADS increases precision and headshot damage",                         ETraitCategory::Special,    PrecisionSlots));
    Registry.Add(EExoticTrait::FiringLine,        FExoticTraitData("Firing Line",             "Damage bonus when near allies",                                                 ETraitCategory::Special,    AllSlots));
    Registry.Add(EExoticTrait::AdrenalineJunkie,  FExoticTraitData("Adrenaline Junkie",       "Stacks damage and reload buffs on kills",                                        ETraitCategory::Special,    AllSlots));
    Registry.Add(EExoticTrait::EyeOfTheStorm,      FExoticTraitData("Eye of the Storm",         "Accuracy and stability improve as magazine depletes",                            ETraitCategory::Special,    AllSlots));
    // clang-format on
}

TArray<FExoticTraitData> UExoticTraitDatabase::GetTraitsForSlot(EWeaponSlot Slot)
{
    EnsureRegistryBuilt();
    TArray<FExoticTraitData> Result;
    for (const auto& Pair : GetRegistry())
    {
        if (Pair.Value.ValidSlots.Contains(Slot))
            Result.Add(Pair.Value);
    }
    return Result;
}

FExoticTraitData UExoticTraitDatabase::GetTraitData(EExoticTrait Trait)
{
    EnsureRegistryBuilt();
    if (auto* Data = GetRegistry().Find(Trait))
        return *Data;
    return FExoticTraitData();
}

TArray<FExoticTraitData> UExoticTraitDatabase::GetTraitsByCategory(ETraitCategory Category)
{
    EnsureRegistryBuilt();
    TArray<FExoticTraitData> Result;
    for (const auto& Pair : GetRegistry())
    {
        if (Pair.Value.Category == Category)
            Result.Add(Pair.Value);
    }
    return Result;
}

FString UExoticTraitDatabase::GetTraitName(EExoticTrait Trait)
{
    const UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EExoticTrait"), true);
    if (Enum)
        return Enum->GetNameStringByValue(static_cast<int64>(Trait));
    return TEXT("Unknown");
}

FString UExoticTraitDatabase::GetTraitDescription(EExoticTrait Trait)
{
    return GetTraitData(Trait).Description;
}

TArray<EWeaponSlot> UExoticTraitDatabase::GetValidSlots(EExoticTrait Trait)
{
    return GetTraitData(Trait).ValidSlots;
}
