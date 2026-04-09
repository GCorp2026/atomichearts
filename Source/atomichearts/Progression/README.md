# Weapon XP / Upgrade System — 2026-04-09

## Overview
Weapons gain XP from kills/usage → level up → unlock bonus perks or stat boosts.

## Files Created

### Progression/FWeaponProgressionData.h
Runtime + config structs:
- `FWeaponProgressionState` — CurrentXP, CurrentLevel, TotalKills, Headshots, UnlockedPerks, CurrentRarity
- `FWeaponProgressionData` — Level, XPRequired, DamageBonus, FireRateBonus, UnlockedPerk
- `FRarityUpgradePath` — FromRarity → ToRarity, UpgradeXP cost, stat bonuses

### Progression/UWeaponProgressionComponent.h/.cpp
Attaches to weapon or character. Handles:
- `AddXP(Amount, bIsHeadshot)` — XP from kills/headshots
- `LevelUpIfPossible()` — auto-level when XP threshold reached
- `TryRarityUpgrade()` — upgrade rarity if enough XP banked
- `GetLevelProgress()` — 0.0-1.0 progress bar value

## Progression Model

### XP Table
| Level | Cumulative XP |
|-------|--------------|
| 1→2   | 150 |
| 2→3   | 300 |
| 3→4   | 450 |
| ...   | ... |
| Max   | 50 |

### Level-Up Bonuses
- Every level: +0.5% base damage
- Every 5 levels: unlock a new perk (Rank I → II → III)

### Perk Examples
| Level | Perk | Effect |
|-------|------|--------|
| 5 | Rampage II+1 | +5% Damage, +3% Fire Rate |
| 10 | Headhunter III+1 | +10% Damage, +6% Fire Rate |

### Rarity Upgrades
| Path | XP Cost | Bonus |
|------|---------|-------|
| Common → Uncommon | 5000 | +10% Damage, +5% FireRate |
| Uncommon → Rare | TBD | TBD |

## Events
- `OnXPAdded(Amount, NewTotalXP)` — for UI XP bar
- `OnWeaponLevelUp(NewLevel, XPAwarded, NewPerks, DamageBonus)` — level up VFX/notify
- `OnRarityUpgrade(OldRarity, NewRarity, XPCost)` — rarity change notification

## Usage
```cpp
// On kill:
WeaponProgressionComp->AddXP(100, bIsHeadshot);

// On headshot:
WeaponProgressionComp->AddXP(100, true); // 2x multiplier

// Check upgrade:
if (WeaponProgressionComp->CanUpgradeRarity()) {
    WeaponProgressionComp->TryRarityUpgrade();
}
```
