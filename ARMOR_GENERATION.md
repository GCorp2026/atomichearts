# Armor Generation System - Destiny Cyberpunk

## ARMOR SYSTEM OVERVIEW

## Armor Slots (6)
| Slot | Function |
|------|----------|
| Helmet | Head protection + stats |
| Gauntlets | Arms + weapon handling |
| Chest | Torso protection + abilities |
| Legs | Movement + reserves |
| Class Item | Class-specific + perks |
| Mark/Visor | Cosmetic + faction |

## Stat System (6 Core Stats)
| Stat | Effect |
|------|--------|
| Mobility | Movement speed, jump height, dodge distance |
| Resilience | Max HP, shield strength, damage resist |
| Recovery | HP regen speed, shield recharge rate |
| Discipline | Grenade cooldown reduction |
| Intellect | Super/ultimate cooldown |
| Strength | Melee damage, ability efficiency |

### Stat Roll Ranges per Rarity
| Rarity | Per-Stat Range | Total Possible |
|--------|---------------|----------------|
| Common | 10-30 | 60-180 |
| Uncommon | 20-45 | 120-270 |
| Rare | 35-60 | 210-360 |
| Legendary | 50-80 | 300-480 |
| Exotic | 60-100 | 340-420 |

## Rarity Tiers
| Rarity | Perks | Border Color |
|--------|-------|--------------|
| Common | 1-2 | White |
| Uncommon | 2-3 | Green |
| Rare | 3-4 | Blue |
| Legendary | 4-5 | Purple |
| Exotic | 5 + unique intrinsic | Gold |

## ARMOR PERKS

### Universal Perks
- **Heavy Lifting** — Strength +20
- **Fastball** — Grenade +20
- **Impact Induction** — Melee energy → Grenade energy
- **Bolstering Detonation** — Kill → HP regeneration
- **Rapid Recovery** — Faster revive speed
- **Dynamo** — Super use → weapon damage buff

### Elemental Mods

**Solar:**
- Restoration — Tick-based healing
- Radiance — Enhanced ability regen while burning

**Arc:**
- Conductors — Chain lightning on hit
- Surge — Damage boost while shielded

**Void:**
- Persistence — Damage resist while weakened
- Override — Weaken enemies on ability hit

## EXOTIC ARMOR (25 Total — 5 Per Class)

### Tech Mage Exotics
1. **CHRONO VISOR** — Time Slow triggers on grenade hit
2. **TEMPORAL VEST** — Rally barricade grants speed to allies
3. **PHASE GLOVES** — Dodge extends invisibility duration
4. **ARCANE WARD** — Rift grants damage absorption
5. **CHRONO SHIFT** — Teleport on critical hit

### Chrome Sentinel Exotics
1. **IRON BANNER** — Barricade grants overshield to team
2. **TITAN CRUSH** — Ground pound creates shockwave
3. **SEISMIC STRIKE** — Shoulder charge slows enemies
4. **FORTIFICATION** — Taking damage increases damage resist
5. **UNSTOPPABLE** — Sprint breakes through enemy shields

### Neon Striker Exotics
1. **BLAZE RUNNER** — Sprint leaves fire trail
2. **THUNDER COIL** — Amplified damage increases melee range
3. **MOBILITY SUIT** — Slide launches into air
4. **VOLTAIC** — Shocked enemies chain to nearby foes
5. **EARTHSHAKER** — Multi-kills create void explosions

### Ghost Hunter Exotics
1. **SHADOWSTEP** — Dodging leaves behind decoys
2. **GHOST PROTOCOL** — Marked enemies take increased damage
3. **PHANTOM** — Invisibility lasts longer, grants radar blur
4. **RECKONING** — Precision kills grant ability energy
5. **SPECTRAL** — Tracked enemies highlighted through walls

## PROCEDURAL GENERATION

### Name Generator Algorithm
```
1. Seed → Deterministic RNG sequence
2. Pick Faction (6): Axiom, Neon, Chrome, Ghost, Solaris, Drift
3. Pick Material (4): per faction
4. Pick Slot Type (4-5): slot-specific
5. Combine: "[Faction] [Material] [Suffix]"
```

### Prefix Tables
| Faction | Materials |
|---------|-----------|
| Axiom | Security, Corporate, Tech, Powered |
| Neon | Street, Syndicate, Cyber, Tactical |
| Chrome | Military, Combat, Standard, Tactical |
| Ghost | Recon, Stealth, Shadow, Phantom |
| Solaris | Solar, Radiant, Flame, Light |
| Drift | Void, Cosmic, Eldritch, Madness |

### Suffix by Slot
| Slot | Suffixes |
|------|----------|
| Helmet | Hood, Visor, Crown, Helm, Mask |
| Chest | Plate, Vest, Cuirass, Chestpiece |
| Gauntlets | Grips, Guards, Bracers, Mitts |
| Legs | Greaves, Boots, Legguards, Leggings |
| Class Item | Link, Sigil, Emblem, Crest |
| Mark/Visor | Shroud, Veil, Seal, Edge |

### Example Names
- "Axiom Security Hood"
- "Neon Street Visor"
- "Chrome Military Plate"
- "Ghost Phantom Hood"
- "Solaris Radiant Crown"
- "Drift Eldritch Boots"

## C++ IMPLEMENTATION

```cpp
UENUM(BlueprintType)
enum class EArmorSlot : uint8 { Helmet, Gauntlets, Chest, Legs, ClassItem, Mark };

UENUM(BlueprintType)
enum class EArmorRarity : uint8 { Common, Uncommon, Rare, Legendary, Exotic };

USTRUCT(BlueprintType)
struct FArmorStats {
    int32 Mobility;
    int32 Resilience;
    int32 Recovery;
    int32 Discipline;
    int32 Intellect;
    int32 Strength;
};

USTRUCT(BlueprintType)
struct FArmorGenerateResult {
    FString Name;
    EArmorSlot Slot;
    EArmorRarity Rarity;
    FArmorStats Stats;
    TArray<FString> Perks;
    FString Intrinsic;
    FLinearColor BorderColor;
};

UCLASS()
class UArmorGenerator : public UObject {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    FArmorGenerateResult GenerateArmor(int32 Seed, EArmorSlot Slot, EArmorRarity Rarity);

    UFUNCTION(BlueprintCallable)
    FString GenerateArmorName(EArmorSlot Slot, int32 Seed);

    UFUNCTION(BlueprintCallable)
    FArmorStats GenerateStats(EArmorRarity Rarity, int32 Seed);

    UFUNCTION(BlueprintCallable)
    TArray<FString> SelectPerks(EArmorRarity Rarity, int32 Seed);

private:
    int32 GetStatMin(EArmorRarity Rarity);
    int32 GetStatMax(EArmorRarity Rarity);
    FRandomStream GetSeededStream(int32 Seed);
};
```

## ENEMY DROP SYSTEM

### Drop Rates by Enemy Type
| Enemy Type | Drop Chance | Rarity Range |
|------------|-------------|--------------|
| Common | 5% | Common → Rare |
| Elite | 20% | Uncommon → Rare |
| Boss | 50% | Rare → Legendary |
| Raid Boss | 100% | Legendary → Exotic |

### Farmable Locations
| Location | Enemy Density | Drop Rate | Notes |
|----------|---------------|-----------|-------|
| Patrol Zones | High | Low | Respawn fast |
| Strikes | Medium | Medium | Bonus chest at end |
| Raids | Low | High | Highest tier only |
| Exotic Missions | Medium | Medium | Guaranteed Exotic on completion |

### Difficulty Scaling
- Power Level difference affects drop quality
- +0 to +10: Standard drops
- +10 to +20: Enhanced drops (blue + perks)
- +20+: Master drops (guaranteed purple+)

## SEEDED GENERATION

All armor generation is deterministic by seed:
```
Same Seed + Slot + Rarity = Identical Armor
```

Use cases:
- Loot sharing with friends
- Tournament/Bounty rewards
- Preview system before acquisition
