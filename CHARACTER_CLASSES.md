# Destiny Cyberpunk — Character Classes

## 5 Classes

---

### 1. TECH MAGE (Time Mage) — Crowd Control

**Subclass:** Chronokeeper

**Abilities:**
- **Time Stop (Ultimate)** — Freeze all enemies in area for 4 seconds
- **Time Slow** — Reduce enemy movement/attack speed by 50%
- **Chrono Trap** — Place trap that warps time for enemies
- **Phase Shift** — Become intangible, pass through enemies

**Stats:** Intelligence (skill damage), Chrono Power (ultimate charge), Haste (cooldowns)

**Role:** Crowd control, support, utility

**Weapons:** Pulse Rifles, Trace Rifles

**Perks:** Temporal Anchor, Time Dilation, Phase Walk

---

### 2. CHROME SENTINEL — Tank

**Subclass:** Iron Wall

**Abilities:**
- **Barricade** — Deploy cover that blocks damage
- **Rally Shield** — Buff allies with damage absorption
- **Ground Pound** — Slam attack that stuns
- **Overshield** — Temporary HP buffer

**Stats:** Resilience (HP), Armor (damage reduction), Strength (melee)

**Role:** Tank, protector

**Weapons:** Heavy weapons, shotguns, swords

**Perks:** Unyielding, Last Stand, Iron Will

---

### 3. NEON PHANTOM — Gunslinger

**Subclass:** Quickdraw

**Abilities:**
- **Fan the Hammer** — Rapid fire pistol burst
- **Dodge** — Short cooldown evade
- **Marked for Death** — Bonus damage on marked target
- **Gun Kata** — Increased accuracy while moving

**Stats:** Mobility (speed), Precision (critical damage), Agility (dodge)

**Role:** DPS, flanker

**Weapons:** Hand Cannons, SMGs, Sidearms

**Perks:** Hot Pursuit, Eyes Open, Frontal Assault

---

### 4. GHOST RUNNER — Scout/Stealth

**Subclass:** Shadow

**Abilities:**
- **Vanish** — Become invisible, enemies lose aggro
- **Scout Drone** — Autonomous recon/turret
- **Blink** — Short range teleport
- **EMP Burst** — Disable enemy tech/shields

**Stats:** Stealth (invisibility duration), Tech (hack strength), Speed (travel)

**Role:** Infiltrator, recon

**Weapons:** Scout Rifles, suppressed SMGs, Trace Rifles

**Perks:** Ghost Protocol, Unseen Strike, Blackout

---

### 5. SOLARIS WARDEN — Support/Healer

**Subclass:** Lightbearer

**Abilities:**
- **Healing Rift** — Place healing zone
- **Solar Grenade** — Burn damage over time
- **Revival** — Resurrect downed ally
- **Solar Flare** — Buff ally damage

**Stats:** Restoration (healing), Radiance (ultimate), Benevolence (ally buff)

**Role:** Support, healer

**Weapons:** Auto Rifles, Pulse Rifles, Sidearms

**Perks:** Inner Light, Solar Overflow, Rising Dawn

---

## Class System — Code Structure

```cpp
// EClassType
enum EClassType { TechMage, ChromeSentinel, NeonPhantom, GhostRunner, SolarisWarden };

// UClassAbilityComponent — handles all abilities per class
// UClassStatsComponent — handles class-specific stats
// UClassPerkComponent — class-specific passive perks
```
