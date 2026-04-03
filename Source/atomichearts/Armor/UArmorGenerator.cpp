#include "Armor/UArmorGenerator.h"

const TArray<FString> UArmorGenerator::Factions = {
    TEXT("Axiom"), TEXT("Neon"), TEXT("Chrome"), TEXT("Ghost"), TEXT("Solaris"), TEXT("Drift")
};

const TMap<FString, TArray<FString>> UArmorGenerator::MaterialsByFaction = {
    { TEXT("Axiom"), { TEXT("Security"), TEXT("Corporate"), TEXT("Tech"), TEXT("Powered") } },
    { TEXT("Neon"),  { TEXT("Street"), TEXT("Syndicate"), TEXT("Cyber"), TEXT("Tactical") } },
    { TEXT("Chrome"),{ TEXT("Military"), TEXT("Combat"), TEXT("Standard"), TEXT("Tactical") } },
    { TEXT("Ghost"), { TEXT("Recon"), TEXT("Stealth"), TEXT("Shadow"), TEXT("Phantom") } },
    { TEXT("Solaris"),{ TEXT("Solar"), TEXT("Radiant"), TEXT("Flame"), TEXT("Light") } },
    { TEXT("Drift"), { TEXT("Void"), TEXT("Cosmic"), TEXT("Eldritch"), TEXT("Madness") } }
};

const TMap<EArmorSlot, TArray<FString>> UArmorGenerator::SuffixesBySlot = {
    { EArmorSlot::Helmet,     { TEXT("Hood"), TEXT("Visor"), TEXT("Crown"), TEXT("Helm"), TEXT("Mask") } },
    { EArmorSlot::Gauntlets,  { TEXT("Grips"), TEXT("Guards"), TEXT("Bracers"), TEXT("Mitts") } },
    { EArmorSlot::Chest,      { TEXT("Plate"), TEXT("Vest"), TEXT("Cuirass"), TEXT("Chestpiece") } },
    { EArmorSlot::Legs,       { TEXT("Greaves"), TEXT("Boots"), TEXT("Legguards"), TEXT("Leggings") } },
    { EArmorSlot::ClassItem,  { TEXT("Link"), TEXT("Sigil"), TEXT("Emblem"), TEXT("Crest") } },
    { EArmorSlot::Mark,       { TEXT("Shroud"), TEXT("Veil"), TEXT("Seal"), TEXT("Edge") } }
};

const TMap<FString, TArray<FString>> UArmorGenerator::ExoticNamesByClass = {
    { TEXT("Tech Mage"), {
        TEXT("CHRONO VISOR"), TEXT("TEMPORAL VEST"), TEXT("PHASE GLOVES"),
        TEXT("ARCANE WARD"), TEXT("CHRONO SHIFT")
    }},
    { TEXT("Chrome Sentinel"), {
        TEXT("IRON BANNER"), TEXT("TITAN CRUSH"), TEXT("SEISMIC STRIKE"),
        TEXT("FORTIFICATION"), TEXT("UNSTOPPABLE")
    }},
    { TEXT("Neon Striker"), {
        TEXT("BLAZE RUNNER"), TEXT("THUNDER COIL"), TEXT("MOBILITY SUIT"),
        TEXT("VOLTAIC"), TEXT("EARTHSHAKER")
    }},
    { TEXT("Ghost Hunter"), {
        TEXT("SHADOWSTEP"), TEXT("GHOST PROTOCOL"), TEXT("PHANTOM"),
        TEXT("RECKONING"), TEXT("SPECTRAL")
    }}
};

FArmorGeneratorResult UArmorGenerator::GenerateArmor(int32 Seed, EArmorSlot Slot, EArmorRarity Rarity)
{
    FArmorGeneratorResult Result;
    Result.Seed = Seed;
    Result.Slot = Slot;
    Result.Rarity = Rarity;
    Result.Name = GenerateArmorName(Slot, Seed);
    Result.Stats = GenerateStats(Rarity, Seed);
    Result.Perks = SelectPerks(Rarity, Seed);
    Result.BorderColor = GetBorderColor(Rarity);

    if (Rarity == EArmorRarity::Exotic)
    {
        Result.Intrinsic = GetExoticIntrinsic(Slot, Seed);
    }

    return Result;
}

FString UArmorGenerator::GenerateArmorName(EArmorSlot Slot, int32 Seed)
{
    FRandomStream Stream = GetSeededStream(Seed);
    FString Faction = GetFaction(Seed);
    FString Material = GetMaterial(Faction, Seed);
    FString Suffix = GetSlotSuffix(Slot, Seed);
    return FString::Printf(TEXT("%s %s %s"), *Faction, *Material, *Suffix);
}

FString UArmorGenerator::GetFaction(int32 Seed)
{
    FRandomStream Stream = GetSeededStream(Seed);
    int32 Index = Stream.RandRange(0, Factions.Num() - 1);
    return Factions[Index];
}

FString UArmorGenerator::GetMaterial(const FString& Faction, int32 Seed)
{
    FRandomStream Stream = GetSeededStream(Seed + Faction.Len());
    const TArray<FString>* Materials = MaterialsByFaction.Find(Faction);
    if (Materials)
    {
        int32 Index = Stream.RandRange(0, Materials->Num() - 1);
        return (*Materials)[Index];
    }
    return TEXT("Standard");
}

FString UArmorGenerator::GetSlotSuffix(EArmorSlot Slot, int32 Seed)
{
    FRandomStream Stream = GetSeededStream(Seed * 7);
    const TArray<FString>* Suffixes = SuffixesBySlot.Find(Slot);
    if (Suffixes)
    {
        int32 Index = Stream.RandRange(0, Suffixes->Num() - 1);
        return (*Suffixes)[Index];
    }
    return TEXT("Gear");
}

FArmorStats UArmorGenerator::GenerateStats(EArmorRarity Rarity, int32 Seed)
{
    FRandomStream Stream = GetSeededStream(Seed * 13);
    int32 Min = GetStatMin(Rarity);
    int32 Max = GetStatMax(Rarity);

    float Mob = Stream.RandRange(Min, Max);
    float Res = Stream.RandRange(Min, Max);
    float Rec = Stream.RandRange(Min, Max);
    float Dis = Stream.RandRange(Min, Max);
    float Int = Stream.RandRange(Min, Max);
    float Str = Stream.RandRange(Min, Max);

    return FArmorStats(Mob, Res, Rec, Dis, Int, Str);
}

int32 UArmorGenerator::GetStatMin(EArmorRarity Rarity)
{
    switch (Rarity)
    {
        case EArmorRarity::Common:    return 10;
        case EArmorRarity::Uncommon:  return 20;
        case EArmorRarity::Rare:      return 35;
        case EArmorRarity::Legendary: return 50;
        case EArmorRarity::Exotic:    return 60;
        default:                       return 10;
    }
}

int32 UArmorGenerator::GetStatMax(EArmorRarity Rarity)
{
    switch (Rarity)
    {
        case EArmorRarity::Common:    return 30;
        case EArmorRarity::Uncommon:  return 45;
        case EArmorRarity::Rare:      return 60;
        case EArmorRarity::Legendary: return 80;
        case EArmorRarity::Exotic:    return 100;
        default:                       return 30;
    }
}

TArray<FString> UArmorGenerator::SelectPerks(EArmorRarity Rarity, int32 Seed)
{
    FRandomStream Stream = GetSeededStream(Seed * 17);
    TArray<FString> AllPerks = {
        TEXT("Heavy Lifting"),
        TEXT("Fastball"),
        TEXT("Impact Induction"),
        TEXT("Bolstering Detonation"),
        TEXT("Rapid Recovery"),
        TEXT("Dynamo"),
        TEXT("Restoration"),
        TEXT("Radiance"),
        TEXT("Conductors"),
        TEXT("Surge"),
        TEXT("Persistence"),
        TEXT("Override")
    };

    int32 PerkCount = 0;
    switch (Rarity)
    {
        case EArmorRarity::Common:    PerkCount = Stream.RandRange(1, 2); break;
        case EArmorRarity::Uncommon:  PerkCount = Stream.RandRange(2, 3); break;
        case EArmorRarity::Rare:      PerkCount = Stream.RandRange(3, 4); break;
        case EArmorRarity::Legendary: PerkCount = Stream.RandRange(4, 5); break;
        case EArmorRarity::Exotic:    PerkCount = 5; break;
        default:                       PerkCount = 1;
    }

    TArray<FString> Selected;
    for (int32 i = 0; i < PerkCount && AllPerks.Num() > 0; ++i)
    {
        int32 Index = Stream.RandRange(0, AllPerks.Num() - 1);
        Selected.Add(AllPerks[Index]);
        AllPerks.RemoveAt(Index);
    }

    return Selected;
}

FLinearColor UArmorGenerator::GetBorderColor(EArmorRarity Rarity)
{
    switch (Rarity)
    {
        case EArmorRarity::Common:    return FLinearColor(1.f, 1.f, 1.f, 1.f);
        case EArmorRarity::Uncommon:  return FLinearColor(0.f, 1.f, 0.f, 1.f);
        case EArmorRarity::Rare:      return FLinearColor(0.f, 0.5f, 1.f, 1.f);
        case EArmorRarity::Legendary: return FLinearColor(0.6f, 0.f, 1.f, 1.f);
        case EArmorRarity::Exotic:    return FLinearColor(1.f, 0.8f, 0.f, 1.f);
        default:                       return FLinearColor(1.f, 1.f, 1.f, 1.f);
    }
}

FString UArmorGenerator::GetExoticIntrinsic(EArmorSlot Slot, int32 Seed)
{
    FRandomStream Stream = GetSeededStream(Seed * 23);
    int32 ClassIndex = Stream.RandRange(0, 3);
    FString ClassName;

    const TArray<FString> ClassNames = { TEXT("Tech Mage"), TEXT("Chrome Sentinel"), TEXT("Neon Striker"), TEXT("Ghost Hunter") };
    ClassName = ClassNames.IsValidIndex(ClassIndex) ? ClassNames[ClassIndex] : ClassNames[0];

    const TArray<FString>* Exotics = ExoticNamesByClass.Find(ClassName);
    if (!Exotics) return TEXT("Unknown Exotic");

    int32 ExoticIndex = Seed % Exotics->Num();
    FString ExoticName = (*Exotics)[ExoticIndex];

    TMap<FString, FString> Intrinsics = {
        { TEXT("CHRONO VISOR"),   TEXT("Time Slow triggers on grenade hit") },
        { TEXT("TEMPORAL VEST"),  TEXT("Rally barricade grants speed to allies") },
        { TEXT("PHASE GLOVES"),   TEXT("Dodge extends invisibility duration") },
        { TEXT("ARCANE WARD"),    TEXT("Rift grants damage absorption") },
        { TEXT("CHRONO SHIFT"),   TEXT("Teleport on critical hit") },
        { TEXT("IRON BANNER"),    TEXT("Barricade grants overshield to team") },
        { TEXT("TITAN CRUSH"),    TEXT("Ground pound creates shockwave") },
        { TEXT("SEISMIC STRIKE"), TEXT("Shoulder charge slows enemies") },
        { TEXT("FORTIFICATION"),  TEXT("Taking damage increases damage resist") },
        { TEXT("UNSTOPPABLE"),   TEXT("Sprint breaks through enemy shields") },
        { TEXT("BLAZE RUNNER"),   TEXT("Sprint leaves fire trail") },
        { TEXT("THUNDER COIL"),   TEXT("Amplified damage increases melee range") },
        { TEXT("MOBILITY SUIT"), TEXT("Slide launches into air") },
        { TEXT("VOLTAIC"),        TEXT("Shocked enemies chain to nearby foes") },
        { TEXT("EARTHSHAKER"),    TEXT("Multi-kills create void explosions") },
        { TEXT("SHADOWSTEP"),     TEXT("Dodging leaves behind decoys") },
        { TEXT("GHOST PROTOCOL"), TEXT("Marked enemies take increased damage") },
        { TEXT("PHANTOM"),        TEXT("Invisibility lasts longer, grants radar blur") },
        { TEXT("RECKONING"),      TEXT("Precision kills grant ability energy") },
        { TEXT("SPECTRAL"),       TEXT("Tracked enemies highlighted through walls") }
    };

    FString* Intrinsic = Intrinsics.Find(ExoticName);
    return Intrinsic ? *Intrinsic : TEXT("Unknown intrinsic effect");
}

FRandomStream UArmorGenerator::GetSeededStream(int32 Seed)
{
    return FRandomStream(Seed);
}
