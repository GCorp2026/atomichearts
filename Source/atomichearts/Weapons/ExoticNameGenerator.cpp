// Copyright 2026 Atomic Hearts Team

#include "Weapons/ExoticNameGenerator.h"
#include "Weapons/EWeaponSlot.h"

// ============================================================
// PREFIX POOL (30) - Mythological / Legendary / Abstract
// ============================================================
static const TArray<FString> GPrefixPool = {
    // Mythology
    TEXT("Mjolnir"),     TEXT("Excalibur"),   TEXT("Gungnir"),    TEXT("Trident"),     TEXT("Aegis"),
    TEXT("Pantheon"),    TEXT("Olympus"),      TEXT("Ragnarok"),   TEXT("Niflheim"),    TEXT("Helheim"),
    // Legendary Figures
    TEXT("Mythoclast"),  TEXT("Praetorian"),   TEXT("Sphinx"),      TEXT("Colossus"),    TEXT("Titan"),
    TEXT("Warden"),      TEXT("Sentinel"),     TEXT("Reaver"),      TEXT("Argus"),       TEXT("Leviathan"),
    // Abstract / Cyber
    TEXT("Axiom"),        TEXT("Cipher"),       TEXT("Vector"),      TEXT("Flux"),        TEXT("Paradox"),
    TEXT("Zenith"),      TEXT("Nexus"),        TEXT("Prism"),       TEXT("Rift"),        TEXT("Void"),
    // Unique / Omega
    TEXT("Sovereign"),   TEXT("Absolute"),     TEXT("Eternal"),     TEXT("Infinite"),    TEXT("Omega"),
    TEXT("Onslaught"),   TEXT("Oblivion"),     TEXT("Eclipse"),     TEXT("Vortex"),      TEXT("Helix")
};

// ============================================================
// NICKNAME POOL (54) - Evocative, punchy names
// ============================================================
static const TArray<FString> GNicknamePool = {
    TEXT("Wolfpack"),   TEXT("Desperado"), TEXT("Havoc"),      TEXT("Rift"),       TEXT("Abyss"),
    TEXT("Specter"),    TEXT("Reaper"),    TEXT("Vortex"),     TEXT("Eclipse"),    TEXT("Tempest"),
    TEXT("Onslaught"),  TEXT("Cataclysm"), TEXT("Avalanche"),   TEXT("Tsunami"),    TEXT("Firestorm"),
    TEXT("Thunderstrike"), TEXT("Doom"),   TEXT("Oblivion"),    TEXT("Redemption"), TEXT("Judgment"),
    TEXT("Reckoning"),  TEXT("Annihilation"), TEXT("Salvation"), TEXT("Deliverance"), TEXT("Ascension"),
    TEXT("Transcendence"), TEXT("Singularity"), TEXT("Cascade"), TEXT("Corona"), TEXT("Helix"),
    TEXT("Paradox"),    TEXT("Zenith"),    TEXT("Nadir"),       TEXT("Apex"),       TEXT("Prime"),
    TEXT("Ultra"),      TEXT("Hyper"),     TEXT("Mega"),        TEXT("Giga"),       TEXT("Alpha"),
    TEXT("Omega"),      TEXT("Zero"),      TEXT("Axiom"),       TEXT("Enigma"),     TEXT("Phantom"),
    TEXT("Wraith"),     TEXT("Shade"),     TEXT("Revenant"),    TEXT("Spectre"),    TEXT("Nova"),
    TEXT("Apocalypse"), TEXT("Genesis"),   TEXT("Requiem"),     TEXT("Crescendo"),  TEXT("Eminence"),
    TEXT("Dominion"),   TEXT("Supremacy"), TEXT("Triumph"),     TEXT("Valor"),      TEXT("Wrath")
};

// ============================================================
// BASE NAMES PER WEAPON SLOT (10 each)
// ============================================================
static const TArray<FString> GBaseNames_AR = {
    TEXT("Horn"),     TEXT("Protocol"),  TEXT("System"),    TEXT("Device"),   TEXT("Mechanism"),
    TEXT("Engine"),   TEXT("Core"),      TEXT("Array"),     TEXT("Matrix"),    TEXT("Axiom")
};
static const TArray<FString> GBaseNames_PR = {
    TEXT("Pulse"),    TEXT("Vector"),    TEXT("Cadence"),   TEXT("Rhythm"),    TEXT("Beat"),
    TEXT("Pattern"),  TEXT("Sequence"),  TEXT("Cycle"),     TEXT("Protocol"),  TEXT("Signal")
};
static const TArray<FString> GBaseNames_SR = {
    TEXT("Scope"),    TEXT("Sight"),     TEXT("Eye"),       TEXT("Lens"),      TEXT("Reticle"),
    TEXT("Crosshair"), TEXT("Oracle"),  TEXT("Seer"),      TEXT("Watcher"),    TEXT("Tracker")
};
static const TArray<FString> GBaseNames_HC = {
    TEXT("Kiss"),     TEXT("Bite"),     TEXT("Fang"),      TEXT("Stinger"),   TEXT("Scorpion"),
    TEXT("Viper"),    TEXT("Cobra"),     TEXT("Asp"),       TEXT("Mamba"),     TEXT("Sidewinder")
};
static const TArray<FString> GBaseNames_SMG = {
    TEXT("Fang"),     TEXT("Edge"),      TEXT("Dart"),      TEXT("Bolt"),      TEXT("Spike"),
    TEXT("Blade"),   TEXT("Razor"),     TEXT("Cleaver"),   TEXT("Dirk"),      TEXT("Lance")
};
static const TArray<FString> GBaseNames_SG = {
    TEXT("Hammer"),   TEXT("Breach"),    TEXT("Crusher"),   TEXT("Smasher"),   TEXT("Shredder"),
    TEXT("Ripper"),   TEXT("Splitter"),  TEXT("Eradicator"), TEXT("Breaker"),  TEXT("Obliterator")
};
static const TArray<FString> GBaseNames_RL = {
    TEXT("Launcher"), TEXT("Ordinance"), TEXT("Solution"), TEXT("Execution"), TEXT("Termination"),
    TEXT("Extinction"), TEXT("Annihilation"), TEXT("Salvation"), TEXT("Judgment"), TEXT("Reckoning")
};
static const TArray<FString> GBaseNames_LMG = {
    TEXT("Cannon"),   TEXT("Devastator"), TEXT("Annihilator"), TEXT("Havoc"),   TEXT("Cataclysm"),
    TEXT("Apocalypse"), TEXT("Destroyer"), TEXT("Eradicator"), TEXT("Obliterator"), TEXT("Inferno")
};
static const TArray<FString> GBaseNames_SW = {
    TEXT("Edge"),     TEXT("Blade"),     TEXT("Reaver"),    TEXT("Cleaver"),   TEXT("Render"),
    TEXT("Sunderer"), TEXT("Carver"),    TEXT("Fracture"),  TEXT("Breaker"),   TEXT("Oblivion")
};
static const TArray<FString> GBaseNames_GL = {
    TEXT("Launcher"), TEXT("Mortem"),    TEXT("Barrage"),   TEXT("Devastation"), TEXT("Inferno"),
    TEXT("Cascade"),  TEXT("Conflagration"), TEXT("Cataclysm"), TEXT("Annihilation"), TEXT("Eclipse")
};

// ============================================================
// LORE TEMPLATES (10)
// ============================================================
static const TArray<FLoreTemplate> GLoreTemplates = {
    FLoreTemplate(TEXT("Forged in the chaos of the Corporate Wars, %s was wielded by the first Chrono-Soldiers who fought to reclaim the neon cities."),        2.0f),
    FLoreTemplate(TEXT("The prototype that started it all. %s has never failed its bearer in over a century of combat operations."),                             2.0f),
    FLoreTemplate(TEXT("Hidden in the Neon Bunker for decades, %s now seeks a worthy wielder among the ranks of the new guardians."),                         2.0f),
    FLoreTemplate(TEXT("Forged in the heart of a dying star, %s channels raw stellar energy into every shot fired."),                                          1.5f),
    FLoreTemplate(TEXT("Once wielded by a legendary guardian, %s carries the weight of countless victories earned in the Shadow Wars."),                      1.5f),
    FLoreTemplate(TEXT("Field agents whisper that %s was the last weapon fired before the Great Collapse, its barrel still warm from that final shot."),    1.5f),
    FLoreTemplate(TEXT("Combat veterans call %s \"The %s\" - a name earned through %d years of unbroken service and %d confirmed victories."),                1.0f),
    FLoreTemplate(TEXT("Recovered from the wreckage of the Axiom Fortress, %s pulses with residual energy from the battle that destroyed it."),               1.0f),
    FLoreTemplate(TEXT("Manufactured by a secretive syndicate, %s was designed with a single purpose: total elimination of the target."),                     1.0f),
    FLoreTemplate(TEXT("The AI core embedded in %s remembers every enemy it has ever faced - and learns from each one."),                                      1.0f)
};

const TArray<FString>& GetBaseNameArray(EWeaponSlot Slot)
{
    switch (Slot)
    {
        case EWeaponSlot::Primary_AR:       return GBaseNames_AR;
        case EWeaponSlot::Primary_PR:       return GBaseNames_PR;
        case EWeaponSlot::Primary_SR:       return GBaseNames_SR;
        case EWeaponSlot::Secondary_HC:     return GBaseNames_HC;
        case EWeaponSlot::Secondary_SMG:    return GBaseNames_SMG;
        case EWeaponSlot::Secondary_SG:     return GBaseNames_SG;
        case EWeaponSlot::Heavy_RL:          return GBaseNames_RL;
        case EWeaponSlot::Heavy_LMG:         return GBaseNames_LMG;
        case EWeaponSlot::Heavy_SW:          return GBaseNames_SW;
        case EWeaponSlot::Heavy_GL:          return GBaseNames_GL;
        default:                            return GBaseNames_AR;
    }
}

FString UExoticNameGenerator::GetPrefix(int32 Index)
{
    return GPrefixPool[Index % GPrefixPool.Num()];
}

FString UExoticNameGenerator::GetNickname(int32 Index)
{
    return GNicknamePool[Index % GNicknamePool.Num()];
}

FString UExoticNameGenerator::GenerateName(int32 Seed, EWeaponSlot Slot)
{
    const int32 PrefixIdx = Seed % GPrefixPool.Num();
    const int32 NicknameIdx = (Seed / GPrefixPool.Num()) % GNicknamePool.Num();
    const TArray<FString>& BaseNames = GetBaseNameArray(Slot);
    const int32 BaseIdx = (Seed / (GPrefixPool.Num() * GNicknamePool.Num())) % BaseNames.Num();

    return FString::Printf(TEXT("%s %s '%s'"),
        *GetPrefix(PrefixIdx),
        *BaseNames[BaseIdx],
        *GetNickname(NicknameIdx));
}

FString UExoticNameGenerator::GetBaseName(EWeaponSlot Slot, int32 Index)
{
    const TArray<FString>& BaseNames = GetBaseNameArray(Slot);
    return BaseNames[Index % BaseNames.Num()];
}

TArray<FString> UExoticNameGenerator::GetBaseNamesForSlot(EWeaponSlot Slot)
{
    return GetBaseNameArray(Slot);
}

FString UExoticNameGenerator::GetLoreTemplate(int32 Index)
{
    return GLoreTemplates[Index % GLoreTemplates.Num()].TemplateText;
}
