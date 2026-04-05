// Copyright 2024 Destiny Cyberpunk

#include "Armor/ArmorIntrinsicDatabase.h"

UArmorIntrinsicDatabase::UArmorIntrinsicDatabase() {}

const TMap<EExoticIntrinsic, FExoticIntrinsicDefinition>& UArmorIntrinsicDatabase::GetIntrinsicMap() {
    static TMap<EExoticIntrinsic, FExoticIntrinsicDefinition> IntrinsicMap;

    if (IntrinsicMap.Num() == 0) {
        // Tech Mage intrinsics
        IntrinsicMap.Add(EExoticIntrinsic::TimeSlowOnGrenade, 
            FExoticIntrinsicDefinition{TEXT("Time Slow"), TEXT("Grenade hits create time dilation zones"), 
                EExoticIntrinsic::TimeSlowOnGrenade, true, 0.5f, 15.f, FLinearColor(0.3f, 0.f, 1.f)});
        IntrinsicMap.Add(EExoticIntrinsic::RallyBarricadeSpeed,
            FExoticIntrinsicDefinition{TEXT("Rally Barricade"), TEXT("Barricade increases nearby ally movement speed"),
                EExoticIntrinsic::RallyBarricadeSpeed, true, 0.25f, 0.f, FLinearColor(0.5f, 0.f, 1.f)});
        IntrinsicMap.Add(EExoticIntrinsic::DodgeInvisExtend,
            FExoticIntrinsicDefinition{TEXT("Extended Invis"), TEXT("Dodge extends invisibility duration"),
                EExoticIntrinsic::DodgeInvisExtend, false, 2.f, 0.f, FLinearColor(0.2f, 0.f, 0.8f)});
        IntrinsicMap.Add(EExoticIntrinsic::BlinkChargesAbilities,
            FExoticIntrinsicDefinition{TEXT("Blink Charge"), TEXT("Blink generates ability energy"),
                EExoticIntrinsic::BlinkChargesAbilities, false, 0.1f, 0.f, FLinearColor(0.4f, 0.f, 1.f)});
        IntrinsicMap.Add(EExoticIntrinsic::SeeThroughWalls,
            FExoticIntrinsicDefinition{TEXT("Wall Vision"), TEXT("See enemies through obstacles"),
                EExoticIntrinsic::SeeThroughWalls, false, 30.f, 60.f, FLinearColor(0.6f, 0.f, 1.f)});
        IntrinsicMap.Add(EExoticIntrinsic::TimeFlux,
            FExoticIntrinsicDefinition{TEXT("Time Flux"), TEXT("Abilities affect multiple targets"),
                EExoticIntrinsic::TimeFlux, false, 2.f, 0.f, FLinearColor(0.7f, 0.f, 1.f)});
        IntrinsicMap.Add(EExoticIntrinsic::ParadoxCage,
            FExoticIntrinsicDefinition{TEXT("Paradox Cage"), TEXT("Chance to reverse incoming damage"),
                EExoticIntrinsic::ParadoxCage, false, 0.15f, 0.f, FLinearColor(0.8f, 0.f, 0.8f)});
        IntrinsicMap.Add(EExoticIntrinsic::ChronoHarness,
            FExoticIntrinsicDefinition{TEXT("Chrono Harness"), TEXT("Ultimate recharges nearby allies"),
                EExoticIntrinsic::ChronoHarness, true, 0.25f, 120.f, FLinearColor(0.9f, 0.f, 0.9f)});
        IntrinsicMap.Add(EExoticIntrinsic::WindupGear,
            FExoticIntrinsicDefinition{TEXT("Windup Gear"), TEXT("Cooldowns accelerate when hit"),
                EExoticIntrinsic::WindupGear, false, 0.2f, 0.f, FLinearColor(0.1f, 0.f, 0.9f)});
        IntrinsicMap.Add(EExoticIntrinsic::InfinityLoop,
            FExoticIntrinsicDefinition{TEXT("Infinity Loop"), TEXT("Abilities chain to nearby enemies"),
                EExoticIntrinsic::InfinityLoop, false, 3.f, 0.f, FLinearColor(1.f, 0.f, 1.f)});

        // Chrome Sentinel intrinsics
        IntrinsicMap.Add(EExoticIntrinsic::IronBanner,
            FExoticIntrinsicDefinition{TEXT("Iron Banner"), TEXT("Barricade grants overshield to allies"),
                EExoticIntrinsic::IronBanner, true, 50.f, 20.f, FLinearColor(1.f, 0.5f, 0.f)});
        IntrinsicMap.Add(EExoticIntrinsic::TitanCrush,
            FExoticIntrinsicDefinition{TEXT("Titan Crush"), TEXT("Ground pound creates shockwave"),
                EExoticIntrinsic::TitanCrush, true, 100.f, 30.f, FLinearColor(1.f, 0.6f, 0.f)});
        IntrinsicMap.Add(EExoticIntrinsic::FortressMode,
            FExoticIntrinsicDefinition{TEXT("Fortress Mode"), TEXT("Immobile but invincible"),
                EExoticIntrinsic::FortressMode, true, 0.f, 45.f, FLinearColor(0.8f, 0.4f, 0.f)});
        IntrinsicMap.Add(EExoticIntrinsic::Juggernaut,
            FExoticIntrinsicDefinition{TEXT("Juggernaut"), TEXT("Constant overshield while in combat"),
                EExoticIntrinsic::Juggernaut, false, 30.f, 0.f, FLinearColor(1.f, 0.7f, 0.f)});
        IntrinsicMap.Add(EExoticIntrinsic::RallyPoint,
            FExoticIntrinsicDefinition{TEXT("Rally Point"), TEXT("Allies near barricade regenerate health"),
                EExoticIntrinsic::RallyPoint, false, 5.f, 0.f, FLinearColor(1.f, 0.8f, 0.f)});
        IntrinsicMap.Add(EExoticIntrinsic::Earthquake,
            FExoticIntrinsicDefinition{TEXT("Earthquake"), TEXT("Sprint triggers ground slam"),
                EExoticIntrinsic::Earthquake, true, 80.f, 15.f, FLinearColor(0.9f, 0.3f, 0.f)});
        IntrinsicMap.Add(EExoticIntrinsic::Bulwark,
            FExoticIntrinsicDefinition{TEXT("Bulwark"), TEXT("Barricade lasts indefinitely"),
                EExoticIntrinsic::Bulwark, false, 0.f, 0.f, FLinearColor(1.f, 0.4f, 0.f)});
        IntrinsicMap.Add(EExoticIntrinsic::Unstoppable,
            FExoticIntrinsicDefinition{TEXT("Unstoppable"), TEXT("Cannot be staggered or knocked back"),
                EExoticIntrinsic::Unstoppable, false, 0.f, 0.f, FLinearColor(1.f, 0.2f, 0.f)});
        IntrinsicMap.Add(EExoticIntrinsic::MountainKeep,
            FExoticIntrinsicDefinition{TEXT("Mountain Keep"), TEXT("Massive health pool increase"),
                EExoticIntrinsic::MountainKeep, false, 50.f, 0.f, FLinearColor(0.7f, 0.3f, 0.f)});
        IntrinsicMap.Add(EExoticIntrinsic::LastStand,
            FExoticIntrinsicDefinition{TEXT("Last Stand"), TEXT("Power increases when alone"),
                EExoticIntrinsic::LastStand, false, 0.3f, 0.f, FLinearColor(1.f, 0.1f, 0.f)});

        // Neon Phantom intrinsics
        IntrinsicMap.Add(EExoticIntrinsic::QuickDraw,
            FExoticIntrinsicDefinition{TEXT("Quick Draw"), TEXT("Instant weapon swap and ready"),
                EExoticIntrinsic::QuickDraw, false, 0.f, 0.f, FLinearColor(1.f, 0.f, 0.5f)});
        IntrinsicMap.Add(EExoticIntrinsic::FanTheHammer,
            FExoticIntrinsicDefinition{TEXT("Fan The Hammer"), TEXT("Rapid pistol fire mode"),
                EExoticIntrinsic::FanTheHammer, true, 2.f, 10.f, FLinearColor(1.f, 0.f, 0.8f)});
        IntrinsicMap.Add(EExoticIntrinsic::HotPursuit,
            FExoticIntrinsicDefinition{TEXT("Hot Pursuit"), TEXT("Move faster near enemies"),
                EExoticIntrinsic::HotPursuit, false, 0.25f, 0.f, FLinearColor(1.f, 0.f, 0.3f)});
        IntrinsicMap.Add(EExoticIntrinsic::EyesOpen,
            FExoticIntrinsicDefinition{TEXT("Eyes Open"), TEXT("Always highlight enemy weak points"),
                EExoticIntrinsic::EyesOpen, false, 0.f, 0.f, FLinearColor(1.f, 0.f, 0.6f)});
        IntrinsicMap.Add(EExoticIntrinsic::FrontalAssault,
            FExoticIntrinsicDefinition{TEXT("Frontal Assault"), TEXT("Damage taken converts to health"),
                EExoticIntrinsic::FrontalAssault, false, 0.4f, 0.f, FLinearColor(1.f, 0.f, 0.4f)});
        IntrinsicMap.Add(EExoticIntrinsic::PerfectBalance,
            FExoticIntrinsicDefinition{TEXT("Perfect Balance"), TEXT("No accuracy penalty from movement"),
                EExoticIntrinsic::PerfectBalance, false, 0.f, 0.f, FLinearColor(0.8f, 0.f, 0.5f)});
        IntrinsicMap.Add(EExoticIntrinsic::Trickster,
            FExoticIntrinsicDefinition{TEXT("Trickster"), TEXT("Enemies explode on death"),
                EExoticIntrinsic::Trickster, false, 50.f, 0.f, FLinearColor(1.f, 0.f, 0.9f)});
        IntrinsicMap.Add(EExoticIntrinsic::Blitz,
            FExoticIntrinsicDefinition{TEXT("Blitz"), TEXT("Sprint leaves blinding trail"),
                EExoticIntrinsic::Blitz, true, 10.f, 8.f, FLinearColor(1.f, 0.f, 0.7f)});
        IntrinsicMap.Add(EExoticIntrinsic::SixthSense,
            FExoticIntrinsicDefinition{TEXT("Sixth Sense"), TEXT("Detect nearby enemies through walls"),
                EExoticIntrinsic::SixthSense, false, 15.f, 0.f, FLinearColor(1.f, 0.f, 0.2f)});
        IntrinsicMap.Add(EExoticIntrinsic::Gunslinger,
            FExoticIntrinsicDefinition{TEXT("Gunslinger"), TEXT("Precision kills buff weapon damage"),
                EExoticIntrinsic::Gunslinger, false, 0.2f, 0.f, FLinearColor(1.f, 0.2f, 0.5f)});

        // Ghost Runner intrinsics
        IntrinsicMap.Add(EExoticIntrinsic::Vanish,
            FExoticIntrinsicDefinition{TEXT("Vanish"), TEXT("On-demand invisibility"),
                EExoticIntrinsic::Vanish, true, 0.f, 30.f, FLinearColor(0.2f, 0.2f, 0.2f)});
        IntrinsicMap.Add(EExoticIntrinsic::Phantom,
            FExoticIntrinsicDefinition{TEXT("Phantom"), TEXT("Reduced enemy detection range"),
                EExoticIntrinsic::Phantom, false, 0.5f, 0.f, FLinearColor(0.3f, 0.3f, 0.3f)});
        IntrinsicMap.Add(EExoticIntrinsic::Blackout,
            FExoticIntrinsicDefinition{TEXT("Blackout"), TEXT("Nearest enemy becomes blind"),
                EExoticIntrinsic::Blackout, true, 0.f, 20.f, FLinearColor(0.1f, 0.1f, 0.1f)});
        IntrinsicMap.Add(EExoticIntrinsic::StealthPatrol,
            FExoticIntrinsicDefinition{TEXT("Stealth Patrol"), TEXT("No aggression while hidden"),
                EExoticIntrinsic::StealthPatrol, false, 0.f, 0.f, FLinearColor(0.15f, 0.15f, 0.15f)});
        IntrinsicMap.Add(EExoticIntrinsic::CloakAndDagger,
            FExoticIntrinsicDefinition{TEXT("Cloak and Dagger"), TEXT("Double jump from stealth"),
                EExoticIntrinsic::CloakAndDagger, false, 1.f, 0.f, FLinearColor(0.25f, 0.25f, 0.25f)});
        IntrinsicMap.Add(EExoticIntrinsic::UnseenStrike,
            FExoticIntrinsicDefinition{TEXT("Unseen Strike"), TEXT("First attack from stealth always crits"),
                EExoticIntrinsic::UnseenStrike, false, 2.f, 0.f, FLinearColor(0.35f, 0.35f, 0.35f)});
        IntrinsicMap.Add(EExoticIntrinsic::GhostProtocol,
            FExoticIntrinsicDefinition{TEXT("Ghost Protocol"), TEXT("Disable nearby electronic devices"),
                EExoticIntrinsic::GhostProtocol, true, 0.f, 45.f, FLinearColor(0.4f, 0.4f, 0.4f)});
        IntrinsicMap.Add(EExoticIntrinsic::ShadowDance,
            FExoticIntrinsicDefinition{TEXT("Shadow Dance"), TEXT("Attacks grant brief invisibility"),
                EExoticIntrinsic::ShadowDance, false, 1.f, 0.f, FLinearColor(0.45f, 0.45f, 0.45f)});
        IntrinsicMap.Add(EExoticIntrinsic::Camo,
            FExoticIntrinsicDefinition{TEXT("Camo"), TEXT("Blend with any environment"),
                EExoticIntrinsic::Camo, false, 0.f, 0.f, FLinearColor(0.5f, 0.5f, 0.5f)});
        IntrinsicMap.Add(EExoticIntrinsic::Tracker,
            FExoticIntrinsicDefinition{TEXT("Tracker"), TEXT("See enemy movement trails"),
                EExoticIntrinsic::Tracker, false, 0.f, 0.f, FLinearColor(0.55f, 0.55f, 0.55f)});

        // Solaris Warden intrinsics
        IntrinsicMap.Add(EExoticIntrinsic::HealingRift,
            FExoticIntrinsicDefinition{TEXT("Healing Rift"), TEXT("Placeable healing zone"),
                EExoticIntrinsic::HealingRift, true, 20.f, 25.f, FLinearColor(1.f, 0.8f, 0.2f)});
        IntrinsicMap.Add(EExoticIntrinsic::SolarFlare,
            FExoticIntrinsicDefinition{TEXT("Solar Flare"), TEXT("Buff nearby ally damage"),
                EExoticIntrinsic::SolarFlare, false, 0.25f, 0.f, FLinearColor(1.f, 0.6f, 0.f)});
        IntrinsicMap.Add(EExoticIntrinsic::InnerLight,
            FExoticIntrinsicDefinition{TEXT("Inner Light"), TEXT("Damage dealt grants healing"),
                EExoticIntrinsic::InnerLight, false, 0.3f, 0.f, FLinearColor(1.f, 0.9f, 0.3f)});
        IntrinsicMap.Add(EExoticIntrinsic::SolarOverflow,
            FExoticIntrinsicDefinition{TEXT("Solar Overflow"), TEXT("Abilities overheal and shield"),
                EExoticIntrinsic::SolarOverflow, false, 25.f, 0.f, FLinearColor(1.f, 0.7f, 0.1f)});
        IntrinsicMap.Add(EExoticIntrinsic::RisingDawn,
            FExoticIntrinsicDefinition{TEXT("Rising Dawn"), TEXT("Kills create healing zones"),
                EExoticIntrinsic::RisingDawn, false, 15.f, 0.f, FLinearColor(1.f, 0.85f, 0.4f)});
        IntrinsicMap.Add(EExoticIntrinsic::RadiantMantle,
            FExoticIntrinsicDefinition{TEXT("Radiant Mantle"), TEXT("Allies near rift gain power"),
                EExoticIntrinsic::RadiantMantle, false, 0.15f, 0.f, FLinearColor(1.f, 0.75f, 0.2f)});
        IntrinsicMap.Add(EExoticIntrinsic::Firefly,
            FExoticIntrinsicDefinition{TEXT("Firefly"), TEXT("Precision kills cause explosions"),
                EExoticIntrinsic::Firefly, false, 60.f, 0.f, FLinearColor(1.f, 0.5f, 0.f)});
        IntrinsicMap.Add(EExoticIntrinsic::WarmindProtection,
            FExoticIntrinsicDefinition{TEXT("Warmind Protection"), TEXT("Deployable sentinel drone"),
                EExoticIntrinsic::WarmindProtection, true, 0.f, 60.f, FLinearColor(1.f, 0.65f, 0.15f)});
        IntrinsicMap.Add(EExoticIntrinsic::Lightbearer,
            FExoticIntrinsicDefinition{TEXT("Lightbearer"), TEXT("Resurrect grants invincibility"),
                EExoticIntrinsic::Lightbearer, false, 5.f, 0.f, FLinearColor(1.f, 0.95f, 0.5f)});
        IntrinsicMap.Add(EExoticIntrinsic::Benevolence,
            FExoticIntrinsicDefinition{TEXT("Benevolence"), TEXT("Healing increases ally damage"),
                EExoticIntrinsic::Benevolence, false, 0.2f, 0.f, FLinearColor(1.f, 1.f, 0.6f)});
    }

    return IntrinsicMap;
}

FExoticIntrinsicDefinition UArmorIntrinsicDatabase::GetIntrinsicDefinition(EExoticIntrinsic Intrinsic) const {
    const FExoticIntrinsicDefinition* Def = GetIntrinsicMap().Find(Intrinsic);
    if (Def) {
        return *Def;
    }
    return FExoticIntrinsicDefinition();
}

TArray<EExoticIntrinsic> UArmorIntrinsicDatabase::GetIntrinsicsForClass(EClassType ClassType) const {
    TArray<EExoticIntrinsic> Result;

    switch (ClassType) {
        case EClassType::TechMage:
            Result = {
                EExoticIntrinsic::TimeSlowOnGrenade, EExoticIntrinsic::RallyBarricadeSpeed,
                EExoticIntrinsic::DodgeInvisExtend, EExoticIntrinsic::BlinkChargesAbilities,
                EExoticIntrinsic::SeeThroughWalls, EExoticIntrinsic::TimeFlux,
                EExoticIntrinsic::ParadoxCage, EExoticIntrinsic::ChronoHarness,
                EExoticIntrinsic::WindupGear, EExoticIntrinsic::InfinityLoop
            };
            break;

        case EClassType::ChromeSentinel:
            Result = {
                EExoticIntrinsic::IronBanner, EExoticIntrinsic::TitanCrush,
                EExoticIntrinsic::FortressMode, EExoticIntrinsic::Juggernaut,
                EExoticIntrinsic::RallyPoint, EExoticIntrinsic::Earthquake,
                EExoticIntrinsic::Bulwark, EExoticIntrinsic::Unstoppable,
                EExoticIntrinsic::MountainKeep, EExoticIntrinsic::LastStand
            };
            break;

        case EClassType::NeonPhantom:
            Result = {
                EExoticIntrinsic::QuickDraw, EExoticIntrinsic::FanTheHammer,
                EExoticIntrinsic::HotPursuit, EExoticIntrinsic::EyesOpen,
                EExoticIntrinsic::FrontalAssault, EExoticIntrinsic::PerfectBalance,
                EExoticIntrinsic::Trickster, EExoticIntrinsic::Blitz,
                EExoticIntrinsic::SixthSense, EExoticIntrinsic::Gunslinger
            };
            break;

        case EClassType::GhostRunner:
            Result = {
                EExoticIntrinsic::Vanish, EExoticIntrinsic::Phantom,
                EExoticIntrinsic::Blackout, EExoticIntrinsic::StealthPatrol,
                EExoticIntrinsic::CloakAndDagger, EExoticIntrinsic::UnseenStrike,
                EExoticIntrinsic::GhostProtocol, EExoticIntrinsic::ShadowDance,
                EExoticIntrinsic::Camo, EExoticIntrinsic::Tracker
            };
            break;

        case EClassType::SolarisWarden:
            Result = {
                EExoticIntrinsic::HealingRift, EExoticIntrinsic::SolarFlare,
                EExoticIntrinsic::InnerLight, EExoticIntrinsic::SolarOverflow,
                EExoticIntrinsic::RisingDawn, EExoticIntrinsic::RadiantMantle,
                EExoticIntrinsic::Firefly, EExoticIntrinsic::WarmindProtection,
                EExoticIntrinsic::Lightbearer, EExoticIntrinsic::Benevolence
            };
            break;
    }

    return Result;
}

FString UArmorIntrinsicDatabase::GetIntrinsicDescription(EExoticIntrinsic Intrinsic) {
    const FExoticIntrinsicDefinition* Def = GetIntrinsicMap().Find(Intrinsic);
    return Def ? Def->Description : TEXT("Unknown intrinsic ability");
}

FString UArmorIntrinsicDatabase::GetIntrinsicDisplayName(EExoticIntrinsic Intrinsic) {
    const FExoticIntrinsicDefinition* Def = GetIntrinsicMap().Find(Intrinsic);
    return Def ? Def->IntrinsicName : TEXT("Unknown");
}

FLinearColor UArmorIntrinsicDatabase::GetIntrinsicColor(EExoticIntrinsic Intrinsic) {
    const FExoticIntrinsicDefinition* Def = GetIntrinsicMap().Find(Intrinsic);
    return Def ? Def->GlowColor : FLinearColor::White;
}

float UArmorIntrinsicDatabase::CalculateEffectMagnitude(EExoticIntrinsic Intrinsic, EClassType ClassType) {
    const FExoticIntrinsicDefinition* Def = GetIntrinsicMap().Find(Intrinsic);
    if (!Def) return 0.f;

    // Class-specific multipliers
    float Multiplier = 1.f;
    switch (ClassType) {
        case EClassType::TechMage:
            if (Intrinsic >= EExoticIntrinsic::TimeSlowOnGrenade && Intrinsic <= EExoticIntrinsic::InfinityLoop) {
                Multiplier = 1.2f;
            }
            break;
        case EClassType::ChromeSentinel:
            if (Intrinsic >= EExoticIntrinsic::IronBanner && Intrinsic <= EExoticIntrinsic::LastStand) {
                Multiplier = 1.15f;
            }
            break;
        case EClassType::NeonPhantom:
            if (Intrinsic >= EExoticIntrinsic::QuickDraw && Intrinsic <= EExoticIntrinsic::Gunslinger) {
                Multiplier = 1.25f;
            }
            break;
        case EClassType::GhostRunner:
            if (Intrinsic >= EExoticIntrinsic::Vanish && Intrinsic <= EExoticIntrinsic::Tracker) {
                Multiplier = 1.1f;
            }
            break;
        case EClassType::SolarisWarden:
            if (Intrinsic >= EExoticIntrinsic::HealingRift && Intrinsic <= EExoticIntrinsic::Benevolence) {
                Multiplier = 1.3f;
            }
            break;
    }

    return Def->EffectMagnitude * Multiplier;
}
