# Atomic Hearts — UE5 Architecture

## 1. UE5 Project Structure

```
Content/
  Characters/
    Player/           # ThirdPersonCharacter base
    NPCs/             # Enemy types
    Companions/       # NPC allies
  Weapons/
    Primary/          # Auto, Pulse, Scout
    Secondary/        # Hand Cannon, SMG, Shotgun
    Heavy/            # Rockets, Swords, LMGs
  Zones/
    Shibuya/          # 7 district maps
    Katana/
    Chrome/
    Drift/
    ServerFarm/
    Blackship/
  Activities/
    Strikes/
    Raids/
    Patrol/
    Crucible/
  Lore/
    Entries/
    Documents/
  UI/
    HUD/
    Menus/
    Inventory/

Source/
  atomichearts/
    Core/             # GameInstance, GameMode base
    Characters/       # Player, NPC, Companion classes
    Weapons/          # Weapon base, specific types
    Abilities/        # Grenades, class abilities, supers
    Factions/         # Faction system
    Inventory/        # Loot, gear system
    Missions/         # Quest/strike/raid logic
    AI/               # Enemy AI, behavior trees
    Audio/            # Sound banks
    Animation/        # Anim instances, montages
```

---

## 2. Asset Swap System Design

### Overview
Allows hot-swapping textures and models at runtime via a manifest-driven system. Base assets live in `Content/`, swap assets in `Content/Assets/` under the same directory structure.

### Naming Convention
Both base and swap assets share the same path/name relative to their respective root:
- Base:     `Content/Weapons/Primary/AutoRifle_MK1.uasset`
- Swap:     `Content/Assets/Weapons/Primary/AutoRifle_MK1.uasset`

### manifest.json
Located in the `atomicsoul-assets` repository. Format:
```json
{
  "version": "1.0",
  "swaps": [
    {
      "assetPath": "Weapons/Primary/AutoRifle_MK1",
      "swapPath": "Weapons/Primary/AutoRifle_Cyberpunk",
      "platform": "PC"
    }
  ]
}
```

### AssetSwapManager (C++)
- Singleton UObject, manages loading/unloading swap assets
- Reads `manifest.json` on startup or map load
- Stores original-asset ↔ swap-asset mappings in a `TMap<FSoftObjectPath, FSoftObjectPath>`
- `SwapAsset(UObject* Original, FName SwapId)` — swaps at runtime
- `RevertSwap(UObject* Original)` — restores base asset
- Supports platform-specific overrides via `platform` field

---

## 3. AI Generation Workflow (Nano Banana API)

### Pipeline

1. **Request Generation**
   - Artist/designer submits prompt + parameters via editor panel
   - System calls Nano Banana API with prompt, resolution, style tags
   - Request queued with status tracking (Pending → Generating → Complete/Failed)

2. **Quality Validation**
   - Generated image returned via webhook/polling
   - Automated checks: resolution, aspect ratio, corruption detection
   - Manual review step if auto-check fails
   - Reject → feedback loop back to generation

3. **Auto-Ingest to Content/**
   - On approval, image placed at `Content/Assets/<Category>/<Name>.<ext>`
   - Corresponding manifest.json entry auto-created
   - Asset registered with AssetSwapManager
   - Notification sent to team (Discord/email hook)

### Editor Integration
- Custom SWidget panel in Unreal Editor sidebar
- Shows generation history, status, preview thumbnails
- One-click promote-to-production button

---

## 4. Key C++ Classes

### Core
| Class | Base | Purpose |
|---|---|---|
| `AAtomichartsGameMode` | `AGameModeBase` | Session management, match state, activity rules |
| `AAtomichartsPlayerController` | `APlayerController` | Input routing, HUD overlay, replication |

### Characters
| Class | Base | Purpose |
|---|---|---|
| `AAtomichartsCharacter` | `ABlasterCharacter` | Player character with abilities, weapons, movement |
| `AAtomichartsNPC` | `ACharacter` | Enemy base — AI-controlled, faction-aware |
| `AAtomichartsCompanion` | `ACharacter` | Friendly NPC ally, follows player |

### Systems
| Class | Base | Purpose |
|---|---|---|
| `AWeaponSystemManager` | `AActor` | Weapon spawn, equip, ammo pools, weapon archetypes |
| `UAssetSwapComponent` | `UActorComponent` | Per-actor asset swap logic |
| `UInventoryComponent` | `UActorComponent` | Loot, gear slots, loadouts, item stats |
| `UFactionComponent` | `UActorComponent` | Faction ID, reputation, hostility rules |
| `UProgressionSystem` | `UObject` | XP, leveling, skill trees, milestone unlocks |

### Abilities (Gameplay Ability System)
| Class | Base | Purpose |
|---|---|---|
| `UAtomicAbility` | `UGameplayAbility` | Grenades, class abilities, supers |
| `UAtomicEffect` | `UGameplayEffect` | Damage, buffs, debuffs |

---

## 5. Module Dependencies

```
atomichearts (Primary Game Module)
├── Core
├── Characters
├── Weapons
├── Abilities
├── Factions
├── Inventory
├── Missions
├── AI
├── Audio
├── Animation
└── Dependencies: Engine, OnlineSubsystem, GameplayTasks, AIModule
```

---

## 6. Replication & Networking

- Character state (health, ammo, abilities) replicated via `ReplicateSubobjects`
- Weapon fire authority on server; client-side prediction for responsiveness
- Faction reputation synced via `ReplicatedWeakObject` / `UActorComponent::GetLifetimeReplicatedProps`
- AssetSwapManager state is client-local (no replication needed)
