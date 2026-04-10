# GameEngine Integration Plan

## Overview

This document maps components from the Unreal Engine GameEngine repository to AtomicHearts gaps, identifying integration opportunities for Health, Movement, Weapons, and Gameplay Ability System (GAS).

**Repository Context:**
- GameEngine: Unreal Engine source (`/root/.openclaw/workspace/github/gameengine`)
- AtomicHearts: Cyberpunk RPG project (`/root/.openclaw/workspace/github/atomichearts`)

**Integration Goals:**
1. Replace placeholder ability system with full GAS.
2. Introduce dedicated Health/Attribute component.
3. Enhance weapon mechanics with reusable components.
4. Fill movement gaps (ladder, vaulting) if missing.
5. Maintain AtomicHearts cyberpunk flavor while leveraging engine‑grade systems.

---

## Component Catalog

### Character Systems

| Component | Path | Lines (h/cpp) | Already in AtomicHearts? |
|-----------|------|---------------|--------------------------|
| TP_ThirdPersonCharacter | `Templates/TP_ThirdPerson/Source/TP_ThirdPerson/TP_ThirdPersonCharacter.h` (96) `.cpp` (133) | 229 | Yes (copied) |
| PlatformingCharacter | `Templates/TP_ThirdPerson/Source/TP_ThirdPerson/Variant_Platforming/PlatformingCharacter.h` (194) `.cpp` (367) | 561 | Yes (Variant_Platforming) |
| SideScrollingCharacter | `Templates/TP_ThirdPerson/Source/TP_ThirdPerson/Variant_SideScrolling/SideScrollingCharacter.h` (180) `.cpp` (350) | 530 | Yes (Variant_SideScrolling) |
| CombatCharacter | `Templates/TP_ThirdPerson/Source/TP_ThirdPerson/Variant_Combat/CombatCharacter.h` (334) `.cpp` (547) | 881 | Yes (Variant_Combat) |
| CombatEnemy (AI) | `Templates/TP_ThirdPerson/Source/TP_ThirdPerson/Variant_Combat/AI/CombatEnemy.h` (232) `.cpp` (343) | 575 | Yes (Variant_Combat/AI) |
| CombatAIController | `Templates/TP_ThirdPerson/Source/TP_ThirdPerson/Variant_Combat/AI/CombatAIController.h` (27) `.cpp` (19) | 46 | Yes |
| CombatStateTreeUtility | `Templates/TP_ThirdPerson/Source/TP_ThirdPerson/Variant_Combat/AI/CombatStateTreeUtility.h` (364) `.cpp` (324) | 688 | Yes |

### GameplayAbilities Plugin (GAS)

| File | Path | Lines |
|------|------|-------|
| AttributeSet.h | `Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AttributeSet.h` | 472 |
| GameplayAbility.h | `Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbility.h` | 934 |
| GameplayEffect.h | `Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffect.h` | 2520 |
| AbilitySystemComponent.h | `Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemComponent.h` | 1988 |
| GameplayCueManager.h | `Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayCueManager.h` | (to be counted) |

### Weapon Systems (Shooter Variant)

| Component | Path | Lines | Note |
|-----------|------|-------|------|
| ShooterCharacter | `Templates/TP_FirstPerson/Source/TP_FirstPerson/Variant_Shooter/ShooterCharacter.h` (187) `.cpp` (328) | 515 | First-person shooter template |
| ShooterWeapon | `Templates/TP_FirstPerson/Source/TP_FirstPerson/Variant_Shooter/Weapons/ShooterWeapon.h` (180) `.cpp` (218) | 398 | Base weapon with firing, reloading, ammo |
| ShooterProjectile | `Templates/TP_FirstPerson/Source/TP_FirstPerson/Variant_Shooter/Weapons/ShooterProjectile.h` (?) `.cpp` (167) | ? | Projectile class |
| ShooterNPC (AI) | `Templates/TP_FirstPerson/Source/TP_FirstPerson/Variant_Shooter/AI/ShooterNPC.h` (157) `.cpp` (214) | 371 | Enemy AI for shooter |

### Movement Systems

- CharacterMovementComponent (engine built-in)
- No dedicated ladder/vault component found in templates.

---

## Integration Opportunities

### 1. Health System

**AtomicHearts Gap:**  
- Health is a plain `float` variable inside `ABlasterCharacter`.
- No regeneration, damage resistance, healing‑over‑time, or armor‑as‑attribute.
- Death handling scattered across character classes.

**GameEngine Reference:**  
- **GAS AttributeSet** (`Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AttributeSet.h`) – 472 lines
- **GameplayEffect** (`Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffect.h`) – 2520 lines
- **AbilitySystemComponent** (`Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemComponent.h`) – 1988 lines

**Integration Plan:**  
- Create `UAtomicHeartsAttributeSet` subclass with `Health`, `MaxHealth`, `Shield`, `Armor`, `DamageResistance` etc.
- Attach `UAbilitySystemComponent` to character base class (`AAtomichartsCharacter`).
- Convert existing damage/healing calls to `ApplyGameplayEffect` or `SetAttributeBaseValue`.
- Keep existing HUD updates via attribute change delegates.

**Files to Port/Adapt:**  
- Reference `AttributeSet.h` for property macros and data structures.
- Use `GameplayEffect.h` for damage/healing effect definitions.
- No direct HealthComponent found; use GAS as standard.

**Lines per component:** < 350 (custom AttributeSet)

---

### 2. Ability System

**AtomicHearts Gap:**  
- `UClassAbilityComponent` implements custom cooldowns and ability slots.
- References `AbilitySystemComponent.h` but does not use GAS abilities, effects, or cues.
- No server‑side prediction, replication, or gameplay‑tag integration.

**GameEngine Reference:**  
- **GameplayAbility** (`Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbility.h`) – 934 lines
- **GameplayEffect** (see above)
- **GameplayCue** (`Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayCueManager.h`)
- **AbilitySystemComponent** (see above)

**Integration Plan:**  
- Replace `UClassAbilityComponent` with `UAbilitySystemComponent`.
- Convert each ability type (`TimeSlow`, `ChronoTrap`, …) into a `UGameplayAbility` subclass.
- Map cooldowns to `GameplayEffect` with `Duration` and `Cooldown` tags.
- Use `GameplayCue` for visual/audio feedback (time‑slow VFX, shield bubbles, etc.).
- Keep existing UI cooldown progress bars via attribute/progress delegates.

**Files to Port/Adapt:**  
- Study `GameplayAbility.h` for ability lifecycle and overrides.
- Use `GameplayEffect.h` for cooldown and cost effects.
- Example ability implementations from `GameEngine/Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Private/`.

**Lines per component:** < 350 per ability subclass.

---

### 3. Movement System

**AtomicHearts Gap:**  
- `UAtomicheartsMovementComponent` already provides sprint, slide, double‑jump, dodge, wall‑run.
- Missing ladder climbing, vaulting, mantle, swimming, zip‑line.

**GameEngine Reference:**  
- **CharacterMovementComponent** (`Engine/Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h`) – engine built‑in.
- **PlatformingCharacter** already includes dash, wall‑jump, double‑jump, coyote time.
- **SideScrollingCharacter** includes wall‑jump, soft platforms, drop‑through.

**Integration Plan:**  
- Extend `UAtomicheartsMovementComponent` with ladder/vault detection (ray‑casts) and state machine.
- Use existing UE4 `UCharacterMovementComponent` `CustomMovementMode` for ladder climbing.
- Implement vaulting as a short‑duration animation‑driven root‑motion ability.
- Consider adding `GameplayAbility` for movement‑based abilities (e.g., cyber‑dash) using GAS.

**Files to Port/Adapt:**  
- Reference `PlatformingCharacter.cpp` (367 lines) for dash and wall‑jump implementation.
- Reference `SideScrollingCharacter.cpp` (350 lines) for soft‑collision and drop‑through.
- No ready‑to‑copy ladder component; implement from scratch using UE4 docs.

**Lines per component:** < 350 (ladder/vault extension).

---

### 4. Weapon System Enhancement

**AtomicHearts Gap:**  
- `AWeaponBase` and `ACyberWeapon` classes exist with ammo, firing, reloading.
- No dedicated weapon component for recoil, spread, ammunition management as GAS attributes.
- Inventory component (`UInventoryComponent`) handles item slots.

**GameEngine Reference:**  
- **ShooterWeapon** (`Templates/TP_FirstPerson/Source/TP_FirstPerson/Variant_Shooter/Weapons/ShooterWeapon.h/cpp`) – 398 lines total.
- **GAS‑based weapon attributes** (ammo count, reload speed) can be `AttributeSet` entries.
- **GameplayAbility** for weapon‑specific abilities (fan‑the‑hammer, marked‑for‑death).

**Integration Plan:**  
- Create `UWeaponComponent` that holds ammo, fire‑mode, ADS state, and recoil patterns.
- Connect weapon attributes to GAS (`CurrentAmmo`, `MaxAmmo`, `ReloadSpeed`).
- Convert exotic traits (`EExoticTrait`) into `GameplayEffect` modifiers.
- Keep existing weapon mesh and animation blueprints; inject component logic.

**Files to Port/Adapt:**  
- Reference `ShooterWeapon.cpp` for firing, reloading, ammo management.
- Use GAS references above for attribute integration.
- No direct weapon component to copy; design new component.

**Lines per component:** < 350.

---

### 5. AI Combat System Integration

**AtomicHearts Gap:**  
- Already has `CombatEnemy` and `CombatAIController` from template.
- AI uses StateTree and basic combat behavior.
- Could benefit from GAS‑based health/damage and ability integration.

**GameEngine Reference:**  
- **CombatEnemy** (575 lines) – already present.
- **CombatStateTreeUtility** (688 lines) – AI utility functions.
- **EnvQueryContext_Player/Danger** – environment queries.

**Integration Plan:**  
- Keep existing AI behavior trees and StateTree.
- Replace health float with GAS AttributeSet.
- Allow enemies to use GameplayAbilities for special attacks (e.g., charged attack as ability).
- Use `GameplayEffect` for damage over time, debuffs.

**Files to Port/Adapt:**  
- Modify `CombatEnemy.cpp` to integrate `UAbilitySystemComponent`.
- Keep existing attack traces and montages.

**Lines per component:** < 350 (modifications).

---

### 6. Gameplay Ability System (GAS) Integration

**AtomicHearts Gap:**  
- Header include only; no active GAS usage.

**GameEngine Reference:**  
- Full plugin at `Engine/Plugins/Runtime/GameplayAbilities/`.

**Integration Plan:**  
1. Enable plugin in `atomichearts.uproject`.
2. Add `AbilitySystemComponent` to character base class.
3. Create `UAtomicHeartsAttributeSet` for health, shield, stats.
4. Convert class‑specific abilities (`TimeSlow`, `RallyShield`, …) into `UGameplayAbility` subclasses.
5. Replace `UClassAbilityComponent` calls with `UAbilitySystemComponent` calls.
6. Replicate via `AbilitySystemComponent` built‑in replication.

**Files to Reference:**  
- `GameEngine/Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemComponent.h`
- `GameEngine/Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AttributeSet.h`
- `GameEngine/Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbility.h`
- `GameEngine/Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffect.h`

**Lines per component:** < 350 (ASC integration).

---

## Licensing & Implementation Concerns

- Unreal Engine source is licensed under Epic EULA; using engine code directly in AtomicHearts is permitted as long as the project complies with the Unreal Engine license.
- GAS plugin is part of the engine; no additional licensing needed.
- Ensure any copied code follows Epic’s coding standards and includes proper copyright notices.
- Keep AtomicHearts‑specific modifications isolated in `Source/atomichearts/` directory.

---

## Verification Checklist

- [ ] Integration plan created (this document)
- [ ] GAS plugin enabled in `.uproject`
- [ ] `UAbilitySystemComponent` added to base character
- [ ] `UAtomicHeartsAttributeSet` implemented
- [ ] Health migration from float to attribute
- [ ] Ability classes converted to `UGameplayAbility`
- [ ] Movement extensions (ladder/vault) designed
- [ ] Weapon component skeleton created
- [ ] AI combat GAS integration
- [ ] MemPalace drawer `gameengine/analysis` updated

---

## MemPalace Drawer: `gameengine/analysis`

**Summary:**  
Deep analysis of GameEngine UE5 Template reveals comprehensive character systems (third‑person, platforming, side‑scrolling, combat), AI combat with StateTree, and shooter weapon system. AtomicHearts already includes many of these templates (combat, platforming, side‑scrolling). Primary integration opportunity is Gameplay Ability System (GAS) for health, abilities, weapon attributes, and AI enhancements.

**Key Findings:**  
- **Character Systems:** TP_ThirdPersonCharacter (229 lines), PlatformingCharacter (561 lines) with dash/double‑jump/wall‑jump, SideScrollingCharacter (530 lines) with soft platforms, CombatCharacter (881 lines) with combo/charged attacks.
- **AI Combat:** CombatEnemy (575 lines) uses StateTree, attack traces, danger notification.
- **Weapon System:** ShooterWeapon (398 lines) provides firing, reloading, ammo management.
- **GAS Plugin:** AttributeSet (472 lines), GameplayAbility (934 lines), GameplayEffect (2520 lines), AbilitySystemComponent (1988 lines) – ready for integration.

**Integration Targets:**  
1. Replace `UClassAbilityComponent` with GAS.
2. Add `UAbilitySystemComponent` to `AAtomichartsCharacter`.
3. Create `UAtomicHeartsAttributeSet` for health/shield/armor.
4. Convert abilities (`TimeSlow`, `ChronoTrap`) to `UGameplayAbility`.
5. Enhance weapon system with GAS attributes (ammo, reload speed).
6. Extend movement with ladder/vault using PlatformingCharacter dash/wall‑jump as reference.
7. Integrate GAS into AI combat (CombatEnemy health as attributes).

**Next Steps:**  
1. Create sub‑agents to implement each component.
2. Update `priority-list.md` with integration tasks.
3. Test with existing AtomicHearts content.

---

*Generated by sub‑agent as part of deep analysis of GameEngine UE5 Template.*