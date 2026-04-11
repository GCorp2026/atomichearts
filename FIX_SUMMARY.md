# Fix Summary: UAH_TimeSlowAbility Commit Order Issue

## Issue
The original problem was that `CommitAbility()` was called after `ApplyGameplayEffectSpecToSelf()`, causing resources (energy/cooldown) to be spent even if the effect application fails.

## Analysis
Upon reviewing the code in `UAH_TimeSlowAbility.cpp`, we found that the commit order was already correct: `CommitAbility` is called before applying the gameplay effect. However, the error handling for early exits used `EndAbility(..., true, false)` where the fifth parameter (`bWasCancelled`) was `false`. This could incorrectly indicate that the ability completed successfully when it was actually cancelled due to resource failure.

## Changes Made
1. **Updated error handling for early exits**:
   - `HasAuthority` check failure → `EndAbility(..., true, true)`
   - `ActorInfo` validation failure → `EndAbility(..., true, true)`
   - `CommitAbility` failure → `EndAbility(..., true, true)`

   The fifth parameter (`bWasCancelled`) is now `true` for all failure cases, properly marking the ability as cancelled.

2. **Commit order remains unchanged** – `CommitAbility` is already called before `ApplyGameplayEffectSpecToSelf()`, ensuring resources are checked/spent before any effect is applied.

## Files Modified
- `Source/atomichearts/Abilities/UAH_TimeSlowAbility.cpp`

## Verification
- Line count: 54 lines (under 350 limit)
- No changes to header file (`UAH_TimeSlowAbility.h`)
- No changes to `TimeSlowEffect` class (defined in `TimeMageAbilitySet.h`)

## Result
The ability now correctly commits resources first, and any failure (including missing authority, invalid actor info, or insufficient resources) results in a cancelled ability with proper replication (`bReplicateEndAbility = true`).

---
*Fix applied by subagent on 2026-04-11*

# Fix Summary: Add Stamina, Energy, MoveSpeed as GAS attributes

## Issue
UClassStatsComponent handles MoveSpeed manually as a float, and there were no GAS attributes for Stamina (sprint/dodge costs) and Energy (ability costs). This prevents using Gameplay Abilities for resource management.

## Changes Made
1. **Added three new attributes to `UAtomicHeartsAttributeSet`**:
   - `Stamina` (default 100) – for sprint/dodge costs
   - `Energy` (default 100) – for ability costs
   - `MoveSpeed` (default 600) – replaces manual handling in `UClassStatsComponent`

2. **Header updates (`UAtomicHeartsAttributeSet.h`)**:
   - Added `UPROPERTY` declarations with `ReplicatedUsing` and `ATTRIBUTE_ACCESSORS_BASIC`
   - Added `OnRep_Stamina`, `OnRep_Energy`, `OnRep_MoveSpeed` replication notify functions

3. **Implementation updates (`UAtomicHeartsAttributeSet.cpp`)**:
   - **Constructor**: Added default initialization (Stamina=100, Energy=100, MoveSpeed=600)
   - **PreAttributeChange**: Added clamping for each new attribute (non‑negative for Stamina/Energy, minimum 1.0 for MoveSpeed)
   - **GetLifetimeReplicatedProps**: Added `DOREPLIFETIME_CONDITION_NOTIFY` for each new attribute
   - **Replication notifies**: Added `OnRep_Stamina`, `OnRep_Energy`, `OnRep_MoveSpeed` functions using `GAMEPLAYATTRIBUTE_REPNOTIFY`

## Files Modified
- `Source/atomichearts/Gameplay/UAtomicHeartsAttributeSet.h`
- `Source/atomichearts/Gameplay/UAtomicHeartsAttributeSet.cpp`

## Verification
- Header line count: ~110 lines (under 350 limit)
- Cpp line count: ~215 lines (under 350 limit)
- All new attributes follow the same macro pattern as existing attributes
- Replication, clamping, and default values are consistent with the rest of the attribute set

## Result
The GAS attribute set now includes Stamina, Energy, and MoveSpeed, enabling gameplay abilities to consume stamina/energy and modify movement speed through the standard GAS flow. `UClassStatsComponent` can later be updated to read MoveSpeed from the attribute set instead of its own float.

---
*Fix applied by subagent on 2026-04-11*