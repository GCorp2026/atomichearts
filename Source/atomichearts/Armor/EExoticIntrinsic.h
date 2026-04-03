// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "EExoticIntrinsic.generated.h"

/**
 * Exotic armor intrinsic abilities - one per exotic piece
 * 10 unique intrinsics per class (50 total)
 */
UENUM(BlueprintType)
enum class EExoticIntrinsic : uint8 {
    None = 0,
    // Tech Mage
    TimeSlowOnGrenade,
    RallyBarricadeSpeed,
    DodgeInvisExtend,
    BlinkChargesAbilities,
    SeeThroughWalls,
    TimeFlux,
    ParadoxCage,
    ChronoHarness,
    WindupGear,
    InfinityLoop,
    // Chrome Sentinel
    IronBanner,
    TitanCrush,
    FortressMode,
    Juggernaut,
    RallyPoint,
    Earthquake,
    Bulwark,
    Unstoppable,
    MountainKeep,
    LastStand,
    // Neon Phantom
    QuickDraw,
    FanTheHammer,
    HotPursuit,
    EyesOpen,
    FrontalAssault,
    PerfectBalance,
    Trickster,
    Blitz,
    SixthSense,
    Gunslinger,
    // Ghost Runner
    Vanish,
    Phantom,
    Blackout,
    StealthPatrol,
    CloakAndDagger,
    UnseenStrike,
    GhostProtocol,
    ShadowDance,
    Camo,
    Tracker,
    // Solaris Warden
    HealingRift,
    SolarFlare,
    InnerLight,
    SolarOverflow,
    RisingDawn,
    RadiantMantle,
    Firefly,
    WarmindProtection,
    Lightbearer,
    Benevolence
};
