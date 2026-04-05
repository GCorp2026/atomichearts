// Copyright 2024 Destiny Cyberpunk

#include "Armor/ExoticArmorGenerator.h"
#include "Armor/ArmorIntrinsicDatabase.h"
#include "Armor/ExoticArmorNameGenerator.h"

UExoticArmorGenerator::UExoticArmorGenerator() {}

FGeneratedExoticArmor UExoticArmorGenerator::GenerateExotic(int32 ExoticIndex, EArmorSlot Slot, EClassType ClassType) {
    FGeneratedExoticArmor Result;

    // Clamp index to valid range
    ExoticIndex = FMath::Clamp(ExoticIndex, 0, 9);
    Result.ExoticIndex = ExoticIndex;
    Result.Slot = Slot;
    Result.ClassType = ClassType;

    // Generate name using name generator
    Result.Name = UExoticArmorNameGenerator::GenerateName(ClassType, Slot, ExoticIndex * 100 + static_cast<int32>(Slot));

    // Get intrinsic
    Result.Intrinsic = GetIntrinsicForIndex(ExoticIndex, ClassType);
    Result.IntrinsicDescription = UArmorIntrinsicDatabase::GetIntrinsicDescription(Result.Intrinsic);

    // Generate stats
    Result.Mobility = 60.f;
    Result.Resilience = 60.f;
    Result.Recovery = 60.f;
    Result.Discipline = 60.f;
    Result.Intellect = 60.f;
    Result.Strength = 60.f;

    FArmorStats Stats = GenerateStats(ClassType, ExoticIndex, ExoticIndex);
    Result.Mobility = Stats.Mobility;
    Result.Resilience = Stats.Resilience;
    Result.Recovery = Stats.Recovery;
    Result.Discipline = Stats.Discipline;
    Result.Intellect = Stats.Intellect;
    Result.Strength = Stats.Strength;

    // Visual properties
    Result.NeonColor = GenerateNeonColor(ClassType, Result.Intrinsic);
    Result.ModelVariant = GenerateModelVariant(ExoticIndex);

    // Lore
    Result.Lore = GenerateLore(ClassType, ExoticIndex, Slot);

    // Blockchain ID
    Result.BlockchainID = GenerateBlockchainID(ClassType, Slot, ExoticIndex);
    Result.UniqueID = GetUniqueIDString(ClassType, Slot, ExoticIndex);

    return Result;
}

FGeneratedExoticArmor UExoticArmorGenerator::GenerateRandomExotic(EArmorSlot Slot, EClassType ClassType) {
    FRandomStream Stream(FDateTime::Now().GetTicks());
    int32 RandomIndex = Stream.RandHelper(10);
    return GenerateExotic(RandomIndex, Slot, ClassType);
}

EExoticIntrinsic UExoticArmorGenerator::GetIntrinsicForIndex(int32 Index, EClassType ClassType) {
    TArray<EExoticIntrinsic> Intrinsics = UArmorIntrinsicDatabase::GetIntrinsicsForClass(ClassType);
    if (Intrinsics.IsValidIndex(Index)) {
        return Intrinsics[Index];
    }
    return EExoticIntrinsic::None;
}

FString UExoticArmorGenerator::GenerateLore(EClassType ClassType, int32 ExoticIndex, EArmorSlot Slot) {
    const TMap<EClassType, TArray<FString>>& LoreMap = GetLoreByClass();
    const TArray<FString>* LoreArray = LoreMap.Find(ClassType);

    if (LoreArray && LoreArray->IsValidIndex(ExoticIndex)) {
        return (*LoreArray)[ExoticIndex];
    }
    return TEXT("A fragment of forgotten legend from the dark age.");
}

FGuid UExoticArmorGenerator::GenerateBlockchainID(EClassType ClassType, EArmorSlot Slot, int32 ExoticIndex) {
    // Create a unique GUID based on class, slot, and index
    uint32 HashData[4];
    HashData[0] = static_cast<uint32>(ClassType);
    HashData[1] = static_cast<uint32>(Slot);
    HashData[2] = static_cast<uint32>(ExoticIndex);
    HashData[3] = static_cast<uint32>(FDateTime::Now().GetTicks() % UINT32_MAX);

    return FGuid(HashData[0] ^ HashData[2], HashData[1] ^ HashData[3],
                  HashData[2] ^ HashData[0], HashData[3] ^ HashData[1]);
}

FString UExoticArmorGenerator::GetUniqueIDString(EClassType ClassType, EArmorSlot Slot, int32 ExoticIndex) {
    FString ClassStr = GetClassPrefix(ClassType);
    FString SlotStr = GetSlotPrefix(Slot);
    return FString::Printf(TEXT("EX-%s-%s-%03d"), *ClassStr, *SlotStr, ExoticIndex);
}

FArmorStats UExoticArmorGenerator::GenerateStats(EClassType ClassType, int32 ExoticIndex, int32 Seed) {
    FRandomStream Stream(Seed * 31 + ExoticIndex * 17);

    // Base stats 60-100 for exotics
    float Mob = Stream.RandRange(60.f, 100.f);
    float Res = Stream.RandRange(60.f, 100.f);
    float Rec = Stream.RandRange(60.f, 100.f);
    float Dis = Stream.RandRange(60.f, 100.f);
    float Int = Stream.RandRange(60.f, 100.f);
    float Str = Stream.RandRange(60.f, 100.f);

    // Class-specific boosts
    switch (ClassType) {
        case EClassType::TechMage:
            Int = Stream.RandRange(80.f, 100.f);
            Dis = Stream.RandRange(70.f, 90.f);
            break;
        case EClassType::ChromeSentinel:
            Res = Stream.RandRange(80.f, 100.f);
            Str = Stream.RandRange(70.f, 90.f);
            break;
        case EClassType::NeonPhantom:
            Mob = Stream.RandRange(80.f, 100.f);
            Rec = Stream.RandRange(70.f, 90.f);
            break;
        case EClassType::GhostRunner:
            Mob = Stream.RandRange(80.f, 100.f);
            Dis = Stream.RandRange(70.f, 90.f);
            break;
        case EClassType::SolarisWarden:
            Rec = Stream.RandRange(80.f, 100.f);
            Int = Stream.RandRange(70.f, 90.f);
            break;
    }

    return FArmorStats(Mob, Res, Rec, Dis, Int, Str);
}

FLinearColor UExoticArmorGenerator::GenerateNeonColor(EClassType ClassType, EExoticIntrinsic Intrinsic) {
    // Use intrinsic database color as base
    FLinearColor BaseColor = UArmorIntrinsicDatabase::GetIntrinsicColor(Intrinsic);

    // Add class-specific tint
    switch (ClassType) {
        case EClassType::TechMage:
            return FLinearColor(0.3f, 0.f, 1.f, 1.f); // Purple
        case EClassType::ChromeSentinel:
            return FLinearColor(1.f, 0.5f, 0.f, 1.f); // Orange
        case EClassType::NeonPhantom:
            return FLinearColor(1.f, 0.f, 0.5f, 1.f); // Pink
        case EClassType::GhostRunner:
            return FLinearColor(0.3f, 0.3f, 0.3f, 1.f); // Gray
        case EClassType::SolarisWarden:
            return FLinearColor(1.f, 0.8f, 0.2f, 1.f); // Gold
        default:
            return BaseColor;
    }
}

int32 UExoticArmorGenerator::GenerateModelVariant(int32 Seed) {
    FRandomStream Stream(Seed);
    return Stream.RandHelper(5); // 0-4 model variants
}

FRandomStream UExoticArmorGenerator::GetSeededStream(int32 Seed) {
    return FRandomStream(Seed);
}

FString UExoticArmorGenerator::GetClassPrefix(EClassType ClassType) {
    switch (ClassType) {
        case EClassType::TechMage: return TEXT("TM");
        case EClassType::ChromeSentinel: return TEXT("CS");
        case EClassType::NeonPhantom: return TEXT("NP");
        case EClassType::GhostRunner: return TEXT("GR");
        case EClassType::SolarisWarden: return TEXT("SW");
        default: return TEXT("XX");
    }
}

FString UExoticArmorGenerator::GetSlotPrefix(EArmorSlot Slot) {
    switch (Slot) {
        case EArmorSlot::Helmet: return TEXT("HLM");
        case EArmorSlot::Gauntlets: return TEXT("GNT");
        case EArmorSlot::Chest: return TEXT("CHT");
        case EArmorSlot::Legs: return TEXT("LEG");
        case EArmorSlot::ClassItem: return TEXT("CI");
        default: return TEXT("UNK");
    }
}

const TMap<EClassType, TArray<FString>>& UExoticArmorGenerator::GetLoreByClass() {
    static TMap<EClassType, TArray<FString>> LoreMap;

    if (LoreMap.Num() == 0) {
        LoreMap.Add(EClassType::TechMage, {
            TEXT("Forged in the chrono-laboratories of the Axiom Collective, this device bends time itself to your will."),
            TEXT("Woven from temporal fibers harvested at the moment of a supernova collapse. Time slows for all but you."),
            TEXT("Chrono-tech interface gauntlets that translate intent into temporal displacement."),
            TEXT("Arcane energy matrices embedded in polymer plating create zones where physics bend."),
            TEXT("Phase-shifting alloy that exists in multiple timelines simultaneously."),
            TEXT("Paradox-resistant cage generator. Creates temporal anomalies that trap enemies in loops."),
            TEXT("Harnesses the chronoforce radiating from the user's life force. Each ability charges faster."),
            TEXT("Gear teeth that wind time itself. The longer the battle, the more your abilities accelerate."),
            TEXT("An infinite feedback loop of temporal energy. When activated, time itself becomes your weapon."),
            TEXT("Anchors the wearer to a fixed point in the timestream. Even death becomes...optional.")
        });

        LoreMap.Add(EClassType::ChromeSentinel, {
            TEXT("Banner-grade steel forged in the heart of the Chrome Citadel. An oath made manifest."),
            TEXT("Titanium alloy gauntlets capable of crushing reinforced plating. Nothing stands in your way."),
            TEXT("Combat-rated fortification plating. When activated, the wearer becomes immovable."),
            TEXT("Juggernaut protocol engaged. The more you fight, the harder you are to stop."),
            TEXT("Rally point beacon generates a zone where allies fight with renewed vigor."),
            TEXT("Seismic gauntlets that harness tectonic energy. Every strike creates earth-shaking reverberations."),
            TEXT("Bulwark helm integrated with threat detection. Enemies find no weakness in your defenses."),
            TEXT("Unstoppable momentum plating. Once you start moving, nothing can halt your advance."),
            TEXT("Mountain-grade alloys harvested from the highest peaks. You are as unmovable as stone."),
            TEXT("When all seems lost, this ancient protocol awakens. The last defender becomes the first strike.")
        });

        LoreMap.Add(EClassType::NeonPhantom, {
            TEXT("Quickdraw reflex enhancers that make your weapon part of your hand. Faster than thought."),
            TEXT("Fan-fire modulation systems. When you pull the trigger, the world erupts in neon lead."),
            TEXT("Thermal tracking systems that lock onto targets. If you run, they only burn hotter."),
            TEXT("Enhanced optical sensors scan for threats in every direction. Nothing catches you unaware."),
            TEXT("Frontal assault plating designed for the bold. Aggression is the best defense."),
            TEXT("Balance correction gyros that make every movement precise. Perfection in motion."),
            TEXT("Trickster's cloak that bends perception. They see one thing; you strike another."),
            TEXT("Blitz capacitors charge with every step. The faster you move, the deadlier you become."),
            TEXT("Sixth sense threat detection that goes beyond sight. You feel danger before it arrives."),
            TEXT("Gunslinger neural pathways optimize every shot. Hip fire becomes poetry in motion.")
        });

        LoreMap.Add(EClassType::GhostRunner, {
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
        });

        LoreMap.Add(EClassType::SolarisWarden, {
            TEXT("Healing rift generators create zones of restoration. Even the broken find wholeness here."),
            TEXT("Solar flare emission systems harness the power of a star's corona."),
            TEXT("Inner light activation amplifies the radiance within. Your warmth heals all around you."),
            TEXT("Solar overflow capacitors store solar energy beyond capacity."),
            TEXT("Rising dawn protocols bring hope to the hopeless. Each dawn is another chance."),
            TEXT("Radiant mantle projects an aura of light that burns the darkness away."),
            TEXT("Firefly ignition systems create chain reactions of solar destruction."),
            TEXT("Warmind protection protocols connect to ancient guardian systems."),
            TEXT("Lightbearer resonance synchronizes with the traveler's grace."),
            TEXT("Benevolence aura extends healing beyond yourself. To give is to receive.")
        });
    }

    return LoreMap;
}
