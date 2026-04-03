# Weapon Generation System — Destiny Cyberpunk

## PROBLEM: 2000+ weapons cannot be hand-coded
## SOLUTION: Procedural generation with seeded randomness

---

## Weapon Name Generator

### Name Parts

**Prefixes (Faction-based):**
| Faction | Prefixes |
|---|---|
| Axiom (Corporate) | Protocol, Mainframe, Enforcer, Overkill, Prime |
| Neon (Syndicate) | Street, Viper, Shadow, Jackal |
| Chrome (Military) | Patriot, Duty, Marshal, Eagle, Iron |
| Ghost (Hackers) | Phantom, Cipher, Ghost, Silent, Void |
| Solaris (Energy) | Radiant, Corona, Nova, Solar, Flare |
| Drift (Eldritch) | Abyss, Void, Madness, Rift, Eldritch |

**Base Types:**
| Slot | Names |
|---|---|
| AR | Assault Rifle, Combat Rifle, Battle Rifle |
| PR | Pulse Rifle, Burst Rifle, Repeater |
| SR | Scout Rifle, Sniper, Marksman |
| HC | Hand Cannon, Revolver, Magnum |
| SMG | Submachine Gun, Machine Pistol, Vector |
| SG | Shotgun, Scattergun, Pump |
| RL | Rocket Launcher, Missile Pod, Bazooka |
| LMG | Machine Gun, Suppressor, Minigun |
| SW | Sword, Blade, Katana |
| GL | Grenade Launcher, Mortar, Blaster |

**Suffixes (Perk Descriptor):**
- Elemental: `of the Fire/Ice/Lightning/Void/Solar`
- Stat-based: `of [Damage/Precision/Velocity/Stability]+X`
- Adjective: Swift, Deadly, Eternal, Vengeful

---

## Stat Roll System

### Base Stats (`FWeaponStats`)
```cpp
struct FWeaponStats {
    float BaseDamage;      // 10–150
    float FireRate;        // 0.01–1.0s per shot
    float Range;           // 500–15000
    float Accuracy;        // 0.5–1.0
    float Stability;       // 0.5–1.0 (recoil control)
    float MagazineSize;    // 10–200
    float ReloadSpeed;     // 1.0–4.0s
    float ZoomLevel;       // 1.0–4.0x
    float Handling;        // 0.5–1.0 (aim speed)
    float RPS;             // Rounds per second
};
```

Stats are rolled per weapon using `Slot` and `Rarity` as constraints. Higher rarity = tighter roll ranges toward max stats.

### Rarity Tiers
| Rarity | Perks | Border |
|---|---|---|
| Common | 1–2 | White / Green |
| Uncommon | 2–3 | Blue |
| Rare | 3–4 | Purple |
| Legendary | 4–5 | Orange |
| Exotic | 5 + Unique Trait | Gold |

---

## Perk System

### Categories
1. **Damage** — Rampage, Kill Clip, Multi-Kill Clip
2. **Utility** — Quickdraw, Snapshot, Auto-Loading
3. **Elemental** — Incendiary, Cryo, Shock, Void
4. **Crafted** — Masterwork, Catalyst

Perks are assigned 1–5 per weapon based on rarity tier. Each perk has a rank (I–III) derived from a secondary roll.

---

## Galleria Horn / Exotic-Style Weapons

Five pre-designed exotics (not procedural):

**1. GALLERIA HORN — Bazooka**
- Exotic Heavy Rocket Launcher
- *Unique:* Tracks multiple targets
- Perk: *Wolfpack Rounds* — Homing cluster bombs

**2. THE FABRICATOR — Trace Rifle**
- Exotic Energy Trace
- *Unique:* Creates friend/foe markers
- Perk: *Neural Link* — Damage buff to marked allies

**3. CHROME FURY — Shotgun**
- Exotic Arc Shotgun
- *Unique:* Full auto with extended range
- Perk: *Trench Barrel* — Damage increases with consecutive hits

**4. VOID WALKER — Pulse Rifle**
- Exotic Void Pulse
- *Unique:* Fires seeking projectiles
- Perk: *Desperado* — Faster fire rate after precision kill

**5. SOLARIS EDGE — Sword**
- Exotic Solar Sword
- *Unique:* Throws as projectile, returns
- Perk: *Guillotine* — Heavy attack damage buff

---

## C++ Implementation

```cpp
UCLASS()
class UWeaponGenerator : public UObject {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    FWeaponGenerateResult GenerateWeapon(int32 Seed, EWeaponSlot Slot, EWeaponRarity Rarity);

    UFUNCTION(BlueprintCallable)
    FString GenerateWeaponName(EWeaponSlot Slot, int32 Seed);

    UFUNCTION(BlueprintCallable)
    FWeaponStats GenerateStats(EWeaponSlot Slot, EWeaponRarity Rarity, int32 Seed);

    UFUNCTION(BlueprintCallable)
    TArray<FWeaponPerk> GeneratePerks(EWeaponRarity Rarity, int32 Seed);
};
```

**Seed flow:** `Seed → FNV1aHash → faction index → prefix` then `→ base type → suffix`. Stats and perks use the same seed with independent derived hashes so regeneration is deterministic.

---

## Loot Box System

| Box | Items | Rarity Roll | Notes |
|---|---|---|---|
| Standard | 5 | Common → Uncommon → Rare | — |
| Deluxe | 5 | Rare → Legendary | Every 10 = 1 Premier |
| Premier | 1 | **Guaranteed Exotic** per weapon class | Cannot dupe existing Exotic |

**Duplicate protection:** Premier box tracks seen Exotics per weapon class. If all 5 class exotics are owned, re-roll within the same box tier.

---

*Deterministic seeding ensures every player seeing the same weapon ID gets identical rolls — enabling trading, leaderboards, and spectator modes.*
