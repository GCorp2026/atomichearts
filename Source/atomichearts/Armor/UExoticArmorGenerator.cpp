// Copyright 2024 Destiny Cyberpunk

#include "Armor/UExoticArmorGenerator.h"

const TMap<EClassType, TArray<FString>> UExoticArmorGenerator::ExoticNamesByClass = {
    { EClassType::TechMage, {
        TEXT("Chrono Visor"), TEXT("Temporal Vest"), TEXT("Phase Gloves"),
        TEXT("Arcane Ward"), TEXT("Chrono Shift"), TEXT("Paradox Cage"),
        TEXT("Chrono Harness"), TEXT("Windup Gear"), TEXT("Infinity Loop"), TEXT("Time Anchor")
    }},
    { EClassType::ChromeSentinel, {
        TEXT("Iron Banner"), TEXT("Titan Crush"), TEXT("Fortress Plate"),
        TEXT("Juggernaut"), TEXT("Rally Point"), TEXT("Seismic Gauntlets"),
        TEXT("Bulwark Helm"), TEXT("Unstoppable"), TEXT("Mountain Keep"), TEXT("Last Stand")
    }},
    { EClassType::NeonPhantom, {
        TEXT("Quickdraw"), TEXT("Fan The Hammer"), TEXT("Hot Pursuit"),
        TEXT("Eagle Eye"), TEXT("Frontal Assault"), TEXT("Perfect Balance"),
        TEXT("Trickster's Cloak"), TEXT("Blitz"), TEXT("Sixth Sense"), TEXT("Gunslinger")
    }},
    { EClassType::GhostRunner, {
        TEXT("Vanish"), TEXT("Phantom Protocol"), TEXT("Blackout"),
        TEXT("Stealth Patrol"), TEXT("Cloak and Dagger"), TEXT("Unseen Strike"),
        TEXT("Ghost Protocol"), TEXT("Shadow Dance"), TEXT("Camo"), TEXT("Tracker")
    }},
    { EClassType::SolarisWarden, {
        TEXT("Healing Rift"), TEXT("Solar Flare"), TEXT("Inner Light"),
        TEXT("Solar Overflow"), TEXT("Rising Dawn"), TEXT("Radiant Mantle"),
        TEXT("Firefly"), TEXT("Warmind Protection"), TEXT("Lightbearer"), TEXT("Benevolence")
    }}
};

const TMap<EClassType, TArray<EExoticIntrinsic>> UExoticArmorGenerator::IntrinsicsByClass = {
    { EClassType::TechMage, {
        EExoticIntrinsic::TimeSlowOnGrenade,
        EExoticIntrinsic::RallyBarricadeSpeed,
        EExoticIntrinsic::DodgeInvisExtend,
        EExoticIntrinsic::BlinkChargesAbilities,
        EExoticIntrinsic::SeeThroughWalls,
        EExoticIntrinsic::TimeFlux,
        EExoticIntrinsic::ParadoxCage,
        EExoticIntrinsic::ChronoHarness,
        EExoticIntrinsic::WindupGear,
        EExoticIntrinsic::InfinityLoop
    }},
    { EClassType::ChromeSentinel, {
        EExoticIntrinsic::IronBanner,
        EExoticIntrinsic::TitanCrush,
        EExoticIntrinsic::FortressMode,
        EExoticIntrinsic::Juggernaut,
        EExoticIntrinsic::RallyPoint,
        EExoticIntrinsic::Earthquake,
        EExoticIntrinsic::Bulwark,
        EExoticIntrinsic::Unstoppable,
        EExoticIntrinsic::MountainKeep,
        EExoticIntrinsic::LastStand
    }},
    { EClassType::NeonPhantom, {
        EExoticIntrinsic::QuickDraw,
        EExoticIntrinsic::FanTheHammer,
        EExoticIntrinsic::HotPursuit,
        EExoticIntrinsic::EyesOpen,
        EExoticIntrinsic::FrontalAssault,
        EExoticIntrinsic::PerfectBalance,
        EExoticIntrinsic::Trickster,
        EExoticIntrinsic::Blitz,
        EExoticIntrinsic::SixthSense,
        EExoticIntrinsic::Gunslinger
    }},
    { EClassType::GhostRunner, {
        EExoticIntrinsic::Vanish,
        EExoticIntrinsic::Phantom,
        EExoticIntrinsic::Blackout,
        EExoticIntrinsic::StealthPatrol,
        EExoticIntrinsic::CloakAndDagger,
        EExoticIntrinsic::UnseenStrike,
        EExoticIntrinsic::GhostProtocol,
        EExoticIntrinsic::ShadowDance,
        EExoticIntrinsic::Camo,
        EExoticIntrinsic::Tracker
    }},
    { EClassType::SolarisWarden, {
        EExoticIntrinsic::HealingRift,
        EExoticIntrinsic::SolarFlare,
        EExoticIntrinsic::InnerLight,
        EExoticIntrinsic::SolarOverflow,
        EExoticIntrinsic::RisingDawn,
        EExoticIntrinsic::RadiantMantle,
        EExoticIntrinsic::Firefly,
        EExoticIntrinsic::WarmindProtection,
        EExoticIntrinsic::Lightbearer,
        EExoticIntrinsic::Benevolence
    }}
};

const TMap<EClassType, TArray<TArray<FString>>> UExoticArmorGenerator::PerksByClass = {
    { EClassType::TechMage, {
        { TEXT("Time Under Tension"), TEXT("Particle Deconstruction"), TEXT("Stabilization") },
        { TEXT("Heavy Lifting"), TEXT("Impact Induction"), TEXT("Fastball") },
        { TEXT("Rapid Recovery"), TEXT("Dynamo"), TEXT("Insulation") },
        { TEXT("Glancing Blows"), TEXT("Sprint Dodge"), TEXT("Distribution") },
        { TEXT("Precision Scanner"), TEXT("Danger Zone"), TEXT("Reconstruction") },
        { TEXT("Temporal Dispatch"), TEXT("Overflow"), TEXT("Surge") },
        { TEXT("BattlefieldDispatch"), TEXT("Turn The Tide"), TEXT("Protector") },
        { TEXT("Energy Transition"), TEXT("Momentum Transfer"), TEXT("Hands On") },
        { TEXT("Overcharge"), TEXT("Charge Master"), TEXT("Supercharge") },
        { TEXT("Time Dilation"), TEXT("Chrono Accelerant"), TEXT("Rewind") }
    }},
    { EClassType::ChromeSentinel, {
        { TEXT("Heavy Lifting"), TEXT("Impact Induction"), TEXT("Splash Damage") },
        { TEXT("Thunderstrike"), TEXT("Tectonic Harvest"), TEXT("Earthshaker") },
        { TEXT("Damage Reserve"), TEXT("Resilience"), TEXT("Immortal") },
        { TEXT("Fortress"), TEXT("Towering"), TEXT("Suppression") },
        { TEXT("Rally Force"), TEXT("Combat Restorative"), TEXT("Banner Bearer") },
        { TEXT("Seismic"), TEXT("Aftershock"), TEXT("Pulverize") },
        { TEXT("Front Line"), TEXT("Bulwark"), TEXT("Defiance") },
        { TEXT("Untouchable"), TEXT("Second Wind"), TEXT("Everlasting") },
        { TEXT("Mountain"), TEXT("Peaks"), TEXT("Summit") },
        { TEXT("Last Stand"), TEXT("Battlefield"), TEXT("Reforge") }
    }},
    { EClassType::NeonPhantom, {
        { TEXT("Quickdraw"), TEXT("Snap"), TEXT("Precision") },
        { TEXT("Fan The Hammer"), TEXT("Full Auto"), TEXT("Rampage") },
        { TEXT("Hot Pursuit"), TEXT("Aggressive Tracker"), TEXT("In Pursuit") },
        { TEXT("Eagle Eye"), TEXT("Hawkeye"), TEXT("Far Eye") },
        { TEXT("Frontal Assault"), TEXT("Attack"), TEXT("Aggression") },
        { TEXT("Perfect Balance"), TEXT("Balanced"), TEXT("Stable") },
        { TEXT("Trickster"), TEXT("Misdirection"), TEXT("Juke") },
        { TEXT("Blitz"), TEXT("Charge"), TEXT("On The Run") },
        { TEXT("Sixth Sense"), TEXT("Danger Sense"), TEXT("Alert") },
        { TEXT("Gunslinger"), TEXT("Hip Fire"), TEXT("Snapshot") }
    }},
    { EClassType::GhostRunner, {
        { TEXT("Vanish"), TEXT("Going Dark"), TEXT("Shadow Cloak") },
        { TEXT("Phantom"), TEXT("Spectral"), TEXT("Phase") },
        { TEXT("Blackout"), TEXT("Darkness"), TEXT("Shadow") },
        { TEXT("Stealth Patrol"), TEXT("Recon"), TEXT("Scout") },
        { TEXT("Cloak And Dagger"), TEXT("Quickfang"), TEXT("Backstab") },
        { TEXT("Unseen Strike"), TEXT("Assassin"), TEXT("Deadly") },
        { TEXT("Ghost Protocol"), TEXT("Espionage"), TEXT("Covert") },
        { TEXT("Shadow Dance"), TEXT("Shade"), TEXT("Phantom Strike") },
        { TEXT("Camo"), TEXT("Blend"), TEXT("Concealment") },
        { TEXT("Tracker"), TEXT("Hunt"), TEXT("Prey") }
    }},
    { EClassType::SolarisWarden, {
        { TEXT("Healing Rift"), TEXT("Restoration"), TEXT("Sanctuary") },
        { TEXT("Solar Flare"), TEXT("Ignite"), TEXT("Scorch") },
        { TEXT("Inner Light"), TEXT("Radiant"), TEXT("Ember") },
        { TEXT("Solar Overflow"), TEXT("Capacity"), TEXT("Overwhelming") },
        { TEXT("Rising Dawn"), TEXT("Rebirth"), TEXT("Resurrection") },
        { TEXT("Radiant Mantle"), TEXT("Aura"), TEXT("Presence") },
        { TEXT("Firefly"), TEXT("Dragonfly"), TEXT("Explosion") },
        { TEXT("Warmind Protection"), TEXT("Ward"), TEXT("Shield") },
        { TEXT("Lightbearer"), TEXT("Grace"), TEXT("Guidance") },
        { TEXT("Benevolence"), TEXT("Mercy"), TEXT("Charity") }
    }}
};

UExoticArmorGenerator::UExoticArmorGenerator() {}

FExoticArmorResult UExoticArmorGenerator::GenerateExotic(int32 Index, EArmorSlot Slot, EClassType ClassType)
{
    FExoticArmorResult Result;
    Result.Slot = Slot;
    Result.ClassType = ClassType;
    Result.Rarity = EArmorRarity::Exotic;
    Result.ExoticIndex = Index;
    Result.BorderColor = GetExoticBorderColor();
    Result.Intrinsic = GetIntrinsicForClass(ClassType, Index);
    Result.IntrinsicName = GetIntrinsicName(Result.Intrinsic);
    Result.ArmorName = GetExoticName(ClassType, Index);
    Result.Stats = GenerateExoticStats(ClassType, Index);
    Result.Perks = GetExoticPerks(ClassType, Index);
    Result.LoreEntry = GenerateLore(ClassType, Index, Slot);

    // Generate unique ID
    FString ClassStr;
    switch (ClassType) {
        case EClassType::TechMage: ClassStr = TEXT("TM"); break;
        case EClassType::ChromeSentinel: ClassStr = TEXT("CS"); break;
        case EClassType::NeonPhantom: ClassStr = TEXT("NP"); break;
        case EClassType::GhostRunner: ClassStr = TEXT("GR"); break;
        case EClassType::SolarisWarden: ClassStr = TEXT("SW"); break;
        default: ClassStr = TEXT("XX"); break;
    }
    FString SlotStr;
    switch (Slot) {
        case EArmorSlot::Helmet: SlotStr = TEXT("HLM"); break;
        case EArmorSlot::Gauntlets: SlotStr = TEXT("GNT"); break;
        case EArmorSlot::Chest: SlotStr = TEXT("CHT"); break;
        case EArmorSlot::Legs: SlotStr = TEXT("LEG"); break;
        case EArmorSlot::ClassItem: SlotStr = TEXT("CI"); break;
        case EArmorSlot::Mark: SlotStr = TEXT("MRK"); break;
        default: SlotStr = TEXT("UNK"); break;
    }
    Result.UniqueID = FString::Printf(TEXT("EX-%s-%s-%03d"), *ClassStr, *SlotStr, Index);

    return Result;
}

FString UExoticArmorGenerator::GetIntrinsicName(EExoticIntrinsic Intrinsic)
{
    switch (Intrinsic)
    {
        case EExoticIntrinsic::TimeSlowOnGrenade: return TEXT("Time Slow on Grenade");
        case EExoticIntrinsic::RallyBarricadeSpeed: return TEXT("Rally Barricade Speed");
        case EExoticIntrinsic::DodgeInvisExtend: return TEXT("Dodge Invis Extend");
        case EExoticIntrinsic::BlinkChargesAbilities: return TEXT("Blink Charges Abilities");
        case EExoticIntrinsic::SeeThroughWalls: return TEXT("See Through Walls");
        case EExoticIntrinsic::TimeFlux: return TEXT("Time Flux");
        case EExoticIntrinsic::ParadoxCage: return TEXT("Paradox Cage");
        case EExoticIntrinsic::ChronoHarness: return TEXT("Chrono Harness");
        case EExoticIntrinsic::WindupGear: return TEXT("Windup Gear");
        case EExoticIntrinsic::InfinityLoop: return TEXT("Infinity Loop");
        case EExoticIntrinsic::IronBanner: return TEXT("Iron Banner");
        case EExoticIntrinsic::TitanCrush: return TEXT("Titan Crush");
        case EExoticIntrinsic::FortressMode: return TEXT("Fortress Mode");
        case EExoticIntrinsic::Juggernaut: return TEXT("Juggernaut");
        case EExoticIntrinsic::RallyPoint: return TEXT("Rally Point");
        case EExoticIntrinsic::Earthquake: return TEXT("Earthquake");
        case EExoticIntrinsic::Bulwark: return TEXT("Bulwark");
        case EExoticIntrinsic::Unstoppable: return TEXT("Unstoppable");
        case EExoticIntrinsic::MountainKeep: return TEXT("Mountain Keep");
        case EExoticIntrinsic::LastStand: return TEXT("Last Stand");
        case EExoticIntrinsic::QuickDraw: return TEXT("Quick Draw");
        case EExoticIntrinsic::FanTheHammer: return TEXT("Fan The Hammer");
        case EExoticIntrinsic::HotPursuit: return TEXT("Hot Pursuit");
        case EExoticIntrinsic::EyesOpen: return TEXT("Eyes Open");
        case EExoticIntrinsic::FrontalAssault: return TEXT("Frontal Assault");
        case EExoticIntrinsic::PerfectBalance: return TEXT("Perfect Balance");
        case EExoticIntrinsic::Trickster: return TEXT("Trickster");
        case EExoticIntrinsic::Blitz: return TEXT("Blitz");
        case EExoticIntrinsic::SixthSense: return TEXT("Sixth Sense");
        case EExoticIntrinsic::Gunslinger: return TEXT("Gunslinger");
        case EExoticIntrinsic::Vanish: return TEXT("Vanish");
        case EExoticIntrinsic::Phantom: return TEXT("Phantom");
        case EExoticIntrinsic::Blackout: return TEXT("Blackout");
        case EExoticIntrinsic::StealthPatrol: return TEXT("Stealth Patrol");
        case EExoticIntrinsic::CloakAndDagger: return TEXT("Cloak and Dagger");
        case EExoticIntrinsic::UnseenStrike: return TEXT("Unseen Strike");
        case EExoticIntrinsic::GhostProtocol: return TEXT("Ghost Protocol");
        case EExoticIntrinsic::ShadowDance: return TEXT("Shadow Dance");
        case EExoticIntrinsic::Camo: return TEXT("Camo");
        case EExoticIntrinsic::Tracker: return TEXT("Tracker");
        case EExoticIntrinsic::HealingRift: return TEXT("Healing Rift");
        case EExoticIntrinsic::SolarFlare: return TEXT("Solar Flare");
        case EExoticIntrinsic::InnerLight: return TEXT("Inner Light");
        case EExoticIntrinsic::SolarOverflow: return TEXT("Solar Overflow");
        case EExoticIntrinsic::RisingDawn: return TEXT("Rising Dawn");
        case EExoticIntrinsic::RadiantMantle: return TEXT("Radiant Mantle");
        case EExoticIntrinsic::Firefly: return TEXT("Firefly");
        case EExoticIntrinsic::WarmindProtection: return TEXT("Warmind Protection");
        case EExoticIntrinsic::Lightbearer: return TEXT("Lightbearer");
        case EExoticIntrinsic::Benevolence: return TEXT("Benevolence");
        default: return TEXT("None");
    }
}

FString UExoticArmorGenerator::GenerateLore(EClassType ClassType, int32 ExoticIndex, EArmorSlot Slot)
{
    const TArray<FString> TechMageLore = {
        TEXT("Forged in the chrono-laboratories of the Axiom Collective, this device bends time itself to your will."),
        TEXT("Woven from temporal fibers harvested at the moment of a supernova collapse. Time slows for all but you."),
        TEXT("Chrono-tech interface gauntlets that translate intent into temporal displacement. Reality bends at your command."),
        TEXT("Arcane energy matrices embedded in polymer plating create zones where the laws of physics...bend."),
        TEXT("Phase-shifting alloy that exists in multiple timelines simultaneously. The enemy cannot hit what they cannot find."),
        TEXT("Paradox-resistant cage generator. Creates temporal anomalies that trap enemies in loops of their own actions."),
        TEXT("Harnesses the chronoforce radiating from the user's life force. Each ability charges faster than the last."),
        TEXT("Gear teeth that wind time itself. The longer the battle, the more your abilities accelerate."),
        TEXT("An infinite feedback loop of temporal energy. When activated, time itself becomes your weapon."),
        TEXT("Anchors the wearer to a fixed point in the timestream. Even death becomes...optional.")
    };
    const TArray<FString> ChromeSentinelLore = {
        TEXT("Banner-grade steel forged in the heart of the Chrome Citadel. An oath made manifest in titanium."),
        TEXT("Titanium alloy gauntlets capable of crushing reinforced plating. Nothing stands in your way."),
        TEXT("Combat-rated fortification plating. When activated, the wearer becomes an immovable object."),
        TEXT("Juggernaut protocol engaged. The more you fight, the harder you are to stop."),
        TEXT("Rally point beacon generates a zone where allies fight with renewed vigor and purpose."),
        TEXT("Seismic gauntlets that harness tectonic energy. Every strike creates earth-shaking reverberations."),
        TEXT("Bulwark helm integrated with threat detection. Enemies find no weakness in your defenses."),
        TEXT("Unstoppable momentum plating. Once you start moving, nothing can halt your advance."),
        TEXT("Mountain-grade alloys harvested from the highest peaks. You are as unmovable as stone."),
        TEXT("When all seems lost, this ancient protocol awakens. The last defender becomes the first strike.")
    };
    const TArray<FString> NeonPhantomLore = {
        TEXT("Quickdraw reflex enhancers that make your weapon part of your hand. Faster than thought."),
        TEXT("Fan-fire modulation systems. When you pull the trigger, the world erupts in neon lead."),
        TEXT("Thermal追踪 systems that lock onto targets. If you run, they only burn hotter."),
        TEXT("Enhanced optical sensors scan for threats in every direction. Nothing catches you unaware."),
        TEXT("Frontal assault plating designed for the bold. Aggression is the best defense."),
        TEXT("Balance correction gyros that make every movement precise. Perfection in motion."),
        TEXT("Trickster's cloak that bends perception. They see one thing; you strike another."),
        TEXT("Blitz capacitors charge with every step. The faster you move, the deadlier you become."),
        TEXT("Sixth sense threat detection that goes beyond sight. You feel danger before it arrives."),
        TEXT("Gunslinger neural pathways optimize every shot. Hip fire becomes poetry in motion.")
    };
    const TArray<FString> GhostRunnerLore = {
        TEXT("Vanish protocols turn the user into a ghost. You were here; now you're not."),
        TEXT("Phantom-grade stealth alloy. The shadows welcome you as one of their own."),
        TEXT("Blackout systems plunge enemies into darkness while you remain the only light."),
        TEXT("Stealth patrol sensor arrays map the world without ever being seen."),
        TEXT("Cloak and dagger offense systems. Silence is the loudest statement."),
        TEXT("Unseen strike targeting locks on before they know they're dead."),
        TEXT("Ghost protocol encryption renders you invisible to all detection systems."),
        TEXT("Shadow dance protocols turn movement itself into an art of evasion."),
        TEXT("Adaptive camouflage that makes you one with any environment."),
        TEXT("Tracker algorithms reveal all who pass before you. Nothing escapes notice.")
    };
    const TArray<FString> SolarisWardenLore = {
        TEXT("Healing rift generators create zones of restoration. Even the broken find wholeness here."),
        TEXT("Solar flare emission systems harness the power of a star's corona."),
        TEXT("Inner light activation amplifies the radiance within. Your warmth heals all around you."),
        TEXT("Solar overflow capacitors store solar energy beyond capacity. Power radiates from every pore."),
        TEXT("Rising dawn protocols bring hope to the hopeless. Each dawn is another chance."),
        TEXT("Radiant mantle projects an aura of light that burns the darkness away."),
        TEXT("Firefly ignition systems create chain reactions of solar destruction."),
        TEXT("Warmind protection protocols connect to ancient guardian systems. You are never truly alone."),
        TEXT("Lightbearer resonance synchronizes with the traveler's grace. You carry the light of millions."),
        TEXT("Benevolence aura extends healing beyond yourself. To give is to receive.")
    };

    const TArray<FString>* LoreArray = nullptr;
    switch (ClassType) {
        case EClassType::TechMage: LoreArray = &TechMageLore; break;
        case EClassType::ChromeSentinel: LoreArray = &ChromeSentinelLore; break;
        case EClassType::NeonPhantom: LoreArray = &NeonPhantomLore; break;
        case EClassType::GhostRunner: LoreArray = &GhostRunnerLore; break;
        case EClassType::SolarisWarden: LoreArray = &SolarisWardenLore; break;
        default: return TEXT("Unknown lore fragment.");
    }

    if (LoreArray && LoreArray->IsValidIndex(ExoticIndex)) {
        return (*LoreArray)[ExoticIndex];
    }
    return TEXT("A fragment of forgotten legend.");
}

FRandomStream UExoticArmorGenerator::GetSeededStream(int32 Seed)
{
    return FRandomStream(Seed);
}

FString UExoticArmorGenerator::GetExoticName(EClassType ClassType, int32 Index)
{
    const TArray<FString>* Names = ExoticNamesByClass.Find(ClassType);
    if (Names && Names->IsValidIndex(Index)) {
        return (*Names)[Index];
    }
    return TEXT("Unknown Exotic");
}

EExoticIntrinsic UExoticArmorGenerator::GetIntrinsicForClass(EClassType ClassType, int32 Index)
{
    const TArray<EExoticIntrinsic>* Intrinsics = IntrinsicsByClass.Find(ClassType);
    if (Intrinsics && Intrinsics->IsValidIndex(Index)) {
        return (*Intrinsics)[Index];
    }
    return EExoticIntrinsic::None;
}

TArray<FString> UExoticArmorGenerator::GetExoticPerks(EClassType ClassType, int32 Index)
{
    const TArray<TArray<FString>>* PerksArray = PerksByClass.Find(ClassType);
    if (PerksArray && PerksArray->IsValidIndex(Index)) {
        return (*PerksArray)[Index];
    }
    return TArray<FString>();
}

FArmorStats UExoticArmorGenerator::GenerateExoticStats(EClassType ClassType, int32 Index)
{
    FRandomStream Stream = GetSeededStream(Index * 31 + static_cast<int32>(ClassType) * 17);

    // Exotics always have high stats (60-100 range)
    float Mob = Stream.RandRange(60, 100);
    float Res = Stream.RandRange(60, 100);
    float Rec = Stream.RandRange(60, 100);
    float Dis = Stream.RandRange(60, 100);
    float Int = Stream.RandRange(60, 100);
    float Str = Stream.RandRange(60, 100);

    // Class-specific stat focuses
    switch (ClassType) {
        case EClassType::TechMage:
            Int = Stream.RandRange(80, 100);
            Dis = Stream.RandRange(70, 90);
            break;
        case EClassType::ChromeSentinel:
            Res = Stream.RandRange(80, 100);
            Str = Stream.RandRange(70, 90);
            break;
        case EClassType::NeonPhantom:
            Mob = Stream.RandRange(80, 100);
            Rec = Stream.RandRange(70, 90);
            break;
        case EClassType::GhostRunner:
            Mob = Stream.RandRange(80, 100);
            Dis = Stream.RandRange(70, 90);
            break;
        case EClassType::SolarisWarden:
            Rec = Stream.RandRange(80, 100);
            Int = Stream.RandRange(70, 90);
            break;
    }

    return FArmorStats(Mob, Res, Rec, Dis, Int, Str);
}

FLinearColor UExoticArmorGenerator::GetExoticBorderColor()
{
    // Gold border for exotic rarity
    return FLinearColor(1.f, 0.8f, 0.f, 1.f);
}
