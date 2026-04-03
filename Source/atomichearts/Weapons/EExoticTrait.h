// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EExoticTrait.generated.h"

/**
 * Signature traits for Exotic weapons - 50+ unique exotic traits
 * that define the weapon's special behavior.
 */
UENUM(BlueprintType)
enum class EExoticTrait : uint8
{
    None = 0,
    
    // === Targeting ===
    WolfpackRounds,
    TrackingSystem,
    SeekingProjectiles,
    LaserGuidance,
    SwarmMissiles,
    WallbangShot,
    HeadshotTracking,
    CorpseFinder,
    AOETracking,
    MultiLock,
    
    // === Fire Mode ===
    FullAutoConversion,
    BurstEnhancement,
    ChargeFire,
    SprayPray,
    DoubleFire,
    TripleFire,
    RapidFire,
    SlowMoFire,
    GravityFire,
    PlasmaFire,
    
    // === Elemental ===
    IncendiaryRounds,
    CryoRounds,
    ShockRounds,
    VoidRounds,
    SolarFlare,
    ArcPulse,
    StasisCrystal,
    StrandTangle,
    RadiationPoison,
    Antimatter,
    
    // === Special ===
    PortalShot,
    TimeDilate,
    ShieldPierce,
    PhaseWeapon,
    RicochetMaster,
    ExplosivePayload,
    ClusterBomb,
    FireAndForget,
    CombatRollReload,
    ThreatDetector,
    GhoulRounds,
    ExecutionerRounds,
    CascadeReactor,
    InfiniteAmmo,
    GravityHammer,
    SwordOnGun,
    RocketJump,
    TracerRound,
    MarkedDeath,
    SecondChance,
    Desperado,
    TrenchBarrel,
    AutoLoading,
    Quickdraw,
    Snapshot,
    FirmWare,
    NeuralLink,
    Guillotine
};
