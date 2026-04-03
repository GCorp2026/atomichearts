# Exotic Weapon System Design

## THE CHALLENGE: 1000 Exotic Weapons

Cannot hand-code 1000 weapons. Must procedurally generate with UNIQUE traits.

---

## Exotic Weapon Architecture

Each exotic has:
1. **Name** (procedurally generated from exotic name parts)
2. **Signature Trait** (what makes it unique - NOT just stats)
3. **3-5 Perks** (one is Signature Perk)
4. **Lore Entry** (procedurally generated)
5. **Visual ID** (neon color, model variant)

---

## Signature Trait System

Instead of just stats, exotics have ACTIVE abilities:

```cpp
UENUM(BlueprintType)
enum class EExoticTrait : uint8 {
    // Targeting (10)
    WolfpackRounds,     // Homing cluster bombs
    TrackingSystem,      // Auto-targets enemies
    SeekingProjectiles,  // Projectiles curve to targets
    LaserGuidance,       // Laser-guided projectiles
    SwarmMissiles,       // Multiple tracking missiles
    WallbangShot,        // Penetrates walls
    HeadshotTracking,    // Snaps to head hitboxes
    CorpseFinder,        // Targets enemy corpses
    AOETracking,         // AOE follows target
    MultiLock,           // Locks onto multiple targets

    // Fire Mode (10)
    FullAutoConversion, // Any weapon becomes full auto
    BurstEnhancement,    // Burst becomes faster
    ChargeFire,          // Hold to charge
    SprayPray,           // Extreme spread, high damage
    DoubleFire,          // Fires two projectiles
    TripleFire,          // Fires three projectiles
    RapidFire,           // Massive fire rate boost
    SlowMoFire,          // Projectiles move in slow-mo
    GravityFire,         // Projectiles pull enemies
    PlasmaFire,          // Converts to plasma damage

    // Elemental (10)
    IncendiaryRounds,    // Burn damage over time
    CryoRounds,          // Slow and freeze
    ShockRounds,         // Chain lightning
    VoidRounds,          // Devour and weaken
    SolarFlare,          // Explosive solar damage
    ArcPulse,            // AoE arc pulse
    StasisCrystal,       // Shatters frozen enemies
    StrandTangle,        // Strand suspends enemies
    RadiationPoison,     // Radiation DOT
    Antimatter,          // Void antimatter explosions

    // Special (20)
    PortalShot,          // Projectiles create portals
    TimeDilate,          // Slows time for hit enemies
    ShieldPierce,        // Ignores all shields
    PhaseWeapon,         // Hits through walls
    RicochetMaster,      // Projectiles ricochet
    ExplosivePayload,    // AoE explosion on impact
    ClusterBomb,         // Splits into child projectiles
    FireAndForget,       // Auto-targets after firing
    CombatRollReload,    // Reload on dodge
    ThreatDetector,      // Highlights enemy weak points
    GhoulRounds,          // Bonus damage on low-health
    ExecutionerRounds,   // Bonus vs low-health targets
    CascadeReactor,      // Kills trigger explosions
    InfiniteAmmo,        // No reload, regenerates ammo
    GravityHammer,       // Melee slam creates gravity well
    SwordOnGun,          // Bayonet melee attacks
    RocketJump,          // Firing propels player
    TracerRound,         // Reveals enemy position
    MarkedDeath,         // Marked enemies take more damage
    SecondChance         // Revive on kill (once per life)
};
```

---

## Name Generator

Special exotic name format: `"{Prefix} {Base} '{Nickname}'"`

**Examples:**
- `AXIOM PROTOCOL 'The Fabricator'`
- `VOID WALKER 'Desperado'`
- `GALLERIA HORN 'Wolfpack'`

### Prefix Pools (30+)
| Category | Examples |
|----------|----------|
| Legendary Figures | Mythoclast, Praetorian, Sphinx, Colossus, Titan, Warden, Sentinel, Reaver |
| Mythology | Mjolnir, Excalibur, Gungnir, Trident, Aegis, Pantheon, Olympus, Ragnarok |
| Abstract | Axiom, Void, Nexus, Prism, Rift, Cipher, Vector, Flux, Paradox, Zenith |
| Unique | The, One, Only, Final, Eternal, Infinite, Absolute, Sovereign, Omega |

### Nickname Pools (50+)
Wolfpack, Desperado, Havoc, Rift, Abyss, Specter, Reaper, Specter, Vortex, Havoc, Eclipse, Tempest, Onslaught, Cataclysm, Avalanche, Tsunami, Firestorm, Thunderstrike, Doom, Oblivion, Redemption, Judgment, Reckoning, Annihilation, Salvation, Deliverance, Ascension, Transcendence, Singularity, Cascade, Corona, Helix, Nexus, Paradox, Zenith, Nadir, Apex, Prime, Ultra, Hyper, Mega, Giga, Alpha, Omega, Zero, Axiom, Cipher, Enigma, Phantom, Wraith, Shade, Revenant

### Base Weapon Names
AR: Horn, Protocol, System, Device, Mechanism, Engine, Core, System, Array, Matrix
SMG: Fang, Edge, Dart, Bolt, Spike, Blade, Razor, Cleaver, dirk, Lance
Shotgun: Hammer, Breach, Crusher, Smasher, Shredder, Ripper, Splitter, Eradicator
Sniper: Scope, Sight, Eye, Lens, Reticle, Crosshair, Oracle, Seer, Watcher, Tracker
Pistol: Kiss, Bite, Fang, Stinger, Scorpion, Viper, Cobra, Asp, Mamba, Sidewinder
Heavy: Cannon, Obliterator, Annihilator, Devastator, Eradicator, Punisher, Destroyer, Havoc, Cataclysm, Apocalypse
Rocket: Launcher, Ordinance, Solution, Execution, Termination, Extinction, Annihilation, Salvation, Judgment, Reckoning

---

## 100 Exotics Per Class

10 weapon classes × 100 exotics = **1000 total**

### Example: PRIMARY_AR (Auto Rifles)

```
1.  MYTHCLAST HORN 'Wolfpack'        - WolfpackRounds + ClusterBomb
2.  MJOLNIR PROTOCOL 'Storm'          - ShockRounds + ChainLightning
3.  GUNGNIR SYSTEM 'Precision'       - FullAuto + HeadshotTracking
4.  EXCALIBUR DEVICE 'Guardian'      - ShieldPierce + PhaseWeapon
5.  TRIDENT MECHANISM 'Tsunami'      - WaterPulse + AOETracking
6.  COLOSSUS ENGINE 'Devastation'    - ExplosivePayload + CascadeReactor
7.  SENTINEL ARRAY 'Judgment'         - MarkedDeath + ThreatDetector
8.  PANTHEON CORE 'Salvation'         - SolarFlare + IncendiaryRounds
9.  AXIOM MATRIX 'Paradox'            - TimeDilate + SlowMoFire
10. VOID WALKER 'Desperado'           - PhaseWeapon + RicochetMaster
... (90 more procedurally generated)
```

---

## C++ Exotic Generator

```cpp
UCLASS()
class UExoticWeaponGenerator : public UWeaponGenerator {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    FExoticWeaponResult GenerateExotic(int32 ExoticIndex, EWeaponSlot Slot);

    UFUNCTION(BlueprintCallable)
    FExoticWeaponResult GenerateRandomExotic(EWeaponSlot Slot);

protected:
    TArray<FExoticTraitData> SignatureTraits;
    TArray<FString> Nicknames;
    TArray<FString> Prefixes;
    TArray<FString> BaseNames;

    FString GenerateLore(int32 Seed, FString Name);
    FExoticTrait PickSignatureTrait(int32 Index, EWeaponSlot Slot);
    FLinearColor GetExoticColor(int32 Index);
};
```

---

## Rarity Distribution (per 100)

| Tier | Name       | Drop % | Traits        |
|------|------------|--------|---------------|
| 1    | Common     | 40%    | 3 perks, 1 trait |
| 2    | Rare       | 35%    | 4 perks, 1 trait |
| 3    | Legendary  | 20%    | 4 perks, 1 signature |
| 4    | Mythic     | 5%     | 5 perks, 2 signatures |

---

## Loot Box Integration

- **Premier Box:** Guaranteed exotic (roll 0-99)
- **Exotic Drop Rate:** 2% in Deluxe edition
- **Exotic Focus:** Can target specific weapon class
- **Dupe Protection:** Track owned exotics, increase odds for new ones

---

## Generation Algorithm

```
Seed = Hash(ExoticIndex, WeaponSlot, SeasonNumber)

1. Pick Rarity (weighted random)
2. Pick 1-2 Signature Traits (from slot-appropriate pool)
3. Pick 3-5 Perks (from weapon-type pool + 1 exotic perk)
4. Generate Name: {Prefix[Seed%30]} {BaseName[Seed%10]} '{Nickname[Seed%50]}'
5. Generate Lore: Template + Seed words
6. Assign Visual: ColorGradient[Index%8], ModelVariant[Index%4]
```

---

## Visual Identification

| Tier | Neon Color | Glow Intensity |
|------|------------|----------------|
| Common | White | Low |
| Rare | Blue | Medium |
| Legendary | Purple | High |
| Mythic | Gold + Rainbow | Pulsing |
