# LOOT BOX SYSTEM

## Box Types

| Type | Cost | Items | Rarity Distribution |
|------|------|-------|---------------------|
| **Standard** | 100 Silver | 5 | Common 60%, Uncommon 30%, Rare 8%, Legendary 2% |
| **Deluxe** | 500 Silver | 5 | Uncommon 40%, Rare 40%, Legendary 18%, Exotic 2% |
| **Premier** | FREE (10 Deluxe) | 5 | 1 guaranteed Exotic/Legendary + 4 bonus items |

## Box Contents

**Weapons (3 per box):**
- 1 weapon for player's current class
- 2 weapons random (any class)

**Armor (2 per box):**
- 1 armor piece for current class
- 1 armor piece for current slot

## Counter System

```cpp
UPROPERTY(Replicated)
int32 BoxesPurchasedCounter = 0;  // Resets after Premier

// Every 10 Deluxe boxes = 1 Premier
// 10 -> 11 -> 12 ... -> 19 -> PREMIER UNLOCKED -> Reset to 0
```

## C++ Implementation

```cpp
USTRUCT()
struct FLootBoxResult {
    GENERATED_BODY()
    TArray<FGeneratedItem> Items;
    bool bIsPremier;
    FGeneratedItem PremierItem;
};

UCLASS()
class ULootBoxManager : public UObject {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    FLootBoxResult OpenBox(EBoxType BoxType, int64 PlayerID);
    
    UFUNCTION(BlueprintCallable)
    void AddPurchaseCounter();
    
    UFUNCTION(BlueprintCallable)
    bool IsPremierUnlocked();
    
    UFUNCTION(BlueprintCallable)
    void ResetCounter();
    
    UFUNCTION(BlueprintCallable)
    int32 GetCounter() { return BoxesPurchasedCounter; }
    
protected:
    FGeneratedItem RollItem(EBoxType BoxType);
    EWeaponRarity RollRarity(EBoxType BoxType);
    
    UPROPERTY()
    int32 BoxesPurchasedCounter = 0;
};
```

## Premier Drop Guarantees

| Box Count | Drop |
|-----------|------|
| 10 | Premier weapon (Exotic OR Legendary) |
| 20 | Premier armor (Exotic OR Legendary) |
| 30 | Premier weapon (Exotic guaranteed) |
| 40 | Premier armor (Exotic guaranteed) |
| 50 | **PREMIUM BUNDLE** — 1 Exotic weapon + 1 Exotic armor |

## Duplicate Protection

- Track all items player has received
- Duplicate rolled → convert to "Shard" currency
- Shards used to purchase specific items

## Silver Economy

| Source | Reward |
|--------|--------|
| Daily Login | 50 silver |
| Patrol Mission | 100 silver |
| Strike Complete | 300 silver |
| Raid Complete | 2000 silver |
| PvP Match | 150 silver |

## UI Design

```
┌─────────────────────────────────────┐
│         LOOT BOXES                  │
├─────────────────────────────────────┤
│  [Standard]  [Deluxe]  [Premier]   │
│    100₴       500₴      0₴ (3/10)   │
├─────────────────────────────────────┤
│                                     │
│     [OPEN LOOT BOX BUTTON]          │
│                                     │
├─────────────────────────────────────┤
│  Recent Drops:                      │
│  ✓ Axiom AR-7 "Overkill" (Rare)     │
│  ✓ Chrome Plate (Uncommon)          │
│  ✓ Neon SMG-8 (Rare)               │
│  ...                                │
└─────────────────────────────────────┘
```