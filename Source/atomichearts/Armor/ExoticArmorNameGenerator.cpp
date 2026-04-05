// Copyright 2024 Destiny Cyberpunk

#include "Armor/ExoticArmorNameGenerator.h"
#include "Misc/RandomStream.h"

UExoticArmorNameGenerator::UExoticArmorNameGenerator() {}

const TMap<EClassType, TArray<FString>>& UExoticArmorNameGenerator::GetClassPrefixes() {
    static TMap<EClassType, TArray<FString>> Prefixes;

    if (Prefixes.Num() == 0) {
        Prefixes.Add(EClassType::TechMage, {
            TEXT("Chrono"), TEXT("Temporal"), TEXT("Phase"), TEXT("Arcane"),
            TEXT("Quantum"), TEXT("Paradox"), TEXT("Flux"), TEXT("Temporal"),
            TEXT("Infinity"), TEXT("Time"), TEXT("Warp"), TEXT("Dimensional")
        });

        Prefixes.Add(EClassType::ChromeSentinel, {
            TEXT("Iron"), TEXT("Titan"), TEXT("Fortress"), TEXT("Juggernaut"),
            TEXT("Rally"), TEXT("Seismic"), TEXT("Bulwark"), TEXT("Mountain"),
            TEXT("Steel"), TEXT("Bronze"), TEXT("Granite"), TEXT("Bastion")
        });

        Prefixes.Add(EClassType::NeonPhantom, {
            TEXT("Quickdraw"), TEXT("Fan"), TEXT("Hot"), TEXT("Eagle"),
            TEXT("Frontal"), TEXT("Perfect"), TEXT("Trickster"), TEXT("Blitz"),
            TEXT("Sixth"), TEXT("Gunslinger"), TEXT("Swift"), TEXT("Rapid")
        });

        Prefixes.Add(EClassType::GhostRunner, {
            TEXT("Vanish"), TEXT("Phantom"), TEXT("Blackout"), TEXT("Stealth"),
            TEXT("Cloak"), TEXT("Unseen"), TEXT("Ghost"), TEXT("Shadow"),
            TEXT("Camo"), TEXT("Tracker"), TEXT("Silent"), TEXT("Covert")
        });

        Prefixes.Add(EClassType::SolarisWarden, {
            TEXT("Healing"), TEXT("Solar"), TEXT("Inner"), TEXT("Radiant"),
            TEXT("Rising"), TEXT("Firefly"), TEXT("Warmind"), TEXT("Light"),
            TEXT("Benevolent"), TEXT("Dawn"), TEXT("Sun"), TEXT("Flame")
        });
    }

    return Prefixes;
}

const TMap<EArmorSlot, TArray<FString>>& UExoticArmorNameGenerator::GetSlotBaseNames() {
    static TMap<EArmorSlot, TArray<FString>> BaseNames;

    if (BaseNames.Num() == 0) {
        BaseNames.Add(EArmorSlot::Helmet, {
            TEXT("Visor"), TEXT("Crown"), TEXT("Hood"), TEXT("Helm"),
            TEXT("Mask"), TEXT("Sight"), TEXT("Vision"), TEXT("View")
        });

        BaseNames.Add(EArmorSlot::Gauntlets, {
            TEXT("Gloves"), TEXT("Grips"), TEXT("Gauntlets"), TEXT("Wraps"),
            TEXT("Hands"), TEXT("Claws"), TEXT("Fists"), TEXT("Grab")
        });

        BaseNames.Add(EArmorSlot::Chest, {
            TEXT("Plate"), TEXT("Vest"), TEXT("Chest"), TEXT("Armor"),
            TEXT("Cuirass"), TEXT("Torso"), TEXT("Core"), TEXT("Harness")
        });

        BaseNames.Add(EArmorSlot::Legs, {
            TEXT("Boots"), TEXT("Greaves"), TEXT("Legs"), TEXT("Leggings"),
            TEXT("Treads"), TEXT("Strides"), TEXT("Sprint"), TEXT("Run")
        });

        BaseNames.Add(EArmorSlot::ClassItem, {
            TEXT("Cloak"), TEXT("Mark"), TEXT("Emblem"), TEXT("Cape"),
            TEXT("Banner"), TEXT("Sigil"), TEXT("Token"), TEXT("Charm")
        });
    }

    return BaseNames;
}

const TArray<FString>& UExoticArmorNameGenerator::GetNicknames() {
    static TArray<FString> Nicknames = {
        TEXT(" of the"), TEXT(" of"), TEXT("'s"),
        TEXT(" Prime"), TEXT(" Alpha"), TEXT(" Omega"),
        TEXT(" Mk II"), TEXT(" Mk III"), TEXT(" V"),
        TEXT(" EX"), TEXT(" X"), TEXT(" Zero")
    };

    return Nicknames;
}

FString UExoticArmorNameGenerator::GenerateName(EClassType ClassType, EArmorSlot Slot, int32 Seed) {
    FRandomStream Stream(Seed);

    const TArray<FString>* ClassPrefixArray = GetClassPrefixes().Find(ClassType);
    const TArray<FString>* SlotBaseArray = GetSlotBaseNames().Find(Slot);

    if (!ClassPrefixArray || !SlotBaseArray) {
        return TEXT("Unknown Exotic");
    }

    // Select prefix
    int32 PrefixIndex = Stream.RandHelper(ClassPrefixArray->Num());
    FString Prefix = (*ClassPrefixArray)[PrefixIndex];

    // Select base name
    int32 BaseIndex = Stream.RandHelper(SlotBaseArray->Num());
    FString BaseName = (*SlotBaseArray)[BaseIndex];

    // Sometimes add nickname
    FString Nickname;
    if (Stream.FRand() > 0.6f) {
        int32 NickIndex = Stream.RandHelper(GetNicknames().Num());
        Nickname = GetNicknames()[NickIndex];
    }

    // Sometimes add descriptor
    FString Descriptor;
    if (Stream.FRand() > 0.7f) {
        const TArray<FString> Descriptors = {
            TEXT("Enhanced"), TEXT("Advanced"), TEXT("Elite"),
            TEXT("Prototype"), TEXT("Legendary"), TEXT("Master")
        };
        int32 DescIndex = Stream.RandHelper(Descriptors.Num());
        Descriptor = Descriptors[DescIndex];
        return FString::Printf(TEXT("%s %s %s%s"), *Descriptor, *Prefix, *BaseName, *Nickname);
    }

    return FString::Printf(TEXT("%s %s%s"), *Prefix, *BaseName, *Nickname);
}

FString UExoticArmorNameGenerator::GenerateRandomName(EClassType ClassType, EArmorSlot Slot) {
    FRandomStream Stream(FDateTime::Now().GetTicks());
    int32 Seed = Stream.RandHelper(INT32_MAX);
    return GenerateName(ClassType, Slot, Seed);
}

FString UExoticArmorNameGenerator::GetSlotSuffix(EArmorSlot Slot) {
    switch (Slot) {
        case EArmorSlot::Helmet: return TEXT("Helmet");
        case EArmorSlot::Gauntlets: return TEXT("Gauntlets");
        case EArmorSlot::Chest: return TEXT("Chest");
        case EArmorSlot::Legs: return TEXT("Legs");
        case EArmorSlot::ClassItem: return TEXT("Class Item");
        default: return TEXT("Unknown");
    }
}

FString UExoticArmorNameGenerator::GetClassPrefix(EClassType ClassType) {
    switch (ClassType) {
        case EClassType::TechMage: return TEXT("Chrono");
        case EClassType::ChromeSentinel: return TEXT("Iron");
        case EClassType::NeonPhantom: return TEXT("Swift");
        case EClassType::GhostRunner: return TEXT("Shadow");
        case EClassType::SolarisWarden: return TEXT("Solar");
        default: return TEXT("Unknown");
    }
}

int32 UExoticArmorNameGenerator::GetSeededRandom(int32 Seed, int32 ArraySize) {
    if (ArraySize <= 0) return 0;
    FRandomStream Stream(Seed);
    return Stream.RandHelper(ArraySize);
}
