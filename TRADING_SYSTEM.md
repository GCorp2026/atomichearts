# TRADING SYSTEM DESIGN

## Overview

- Players can list weapons/armor for sale
- Other players can purchase from listings
- 30% commission to the house (developer)
- 70% goes to the seller

---

## Marketplace Structure

```cpp
USTRUCT()
struct FMarketListing {
    GENERATED_BODY()
    UPROPERTY()
    FGuid ListingID;
    
    UPROPERTY()
    int64 SellerID;  // Player who owns item
    
    UPROPERTY()
    FString ItemID;  // Generated Item ID
    
    UPROPERTY()
    FString ItemName;  // "Axiom AR-7 'Overkill'"
    
    UPROPERTY()
    EItemType ItemType;  // Weapon or Armor
    
    UPROPERTY()
    EWeaponRarity Rarity;
    
    UPROPERTY()
    int32 Price;  // In-game currency (Silver)
    
    UPROPERTY()
    int64 ListedAt;  // Timestamp
    
    UPROPERTY()
    FString PreviewStats;  // JSON of item stats
};
```

---

## Commission Structure

| Component | Amount |
|-----------|--------|
| Listing Fee | 10 silver (refunded on sale) |
| Sale Commission | 30% of sale price |

### Example Transaction (100 silver sale)

| Recipient | Amount | Calculation |
|-----------|--------|-------------|
| Seller | 63 silver | 70% of 90 (after listing fee refund) |
| House | 37 silver | 30% commission + 10 listing fee |

---

## C++ Classes

### UMarketplaceManager

Handles all trading logic.

```cpp
UCLASS()
class UMarketplaceManager : public UObject {
    GENERATED_BODY()
public:
    // List item for sale
    UFUNCTION(BlueprintCallable)
    FMarketListing ListItem(FGuid ItemID, int32 Price);
    
    // Purchase item
    UFUNCTION(BlueprintCallable)
    bool PurchaseItem(FGuid ListingID, int64 BuyerID);
    
    // Calculate commission
    UFUNCTION(BlueprintPure)
    int32 CalculateCommission(int32 SalePrice);
    
    // Get seller payout
    UFUNCTION(BlueprintPure)
    int32 CalculateSellerPayout(int32 SalePrice);
    
    // Cancel listing
    UFUNCTION(BlueprintCallable)
    bool CancelListing(FGuid ListingID);
    
    // Get active listings
    UFUNCTION(BlueprintCallable)
    TArray<FMarketListing> GetListings(
        EItemType FilterType = EItemType::Any,
        EWeaponRarity MinRarity = EWeaponRarity::Common,
        int32 MaxPrice = MAX_INT32
    );
};
```

---

## UI Flow

1. **List Item**: Player opens Inventory → Select Item → "List on Marketplace"
2. **Set Price**: Player sets price → Confirm → Item listed (10 silver fee charged)
3. **Browse**: Other players see listings in Marketplace (filterable by type, rarity, price)
4. **Purchase**: Buyer selects item → Confirm → Item transferred, silver deducted/credited

---

## Anti-Exploit Measures

| Measure | Description |
|---------|-------------|
| Item Lock | Items locked during listing (cannot unequip/delete) |
| Relist Cooldown | 24-hour cooldown on relisting same item |
| Listing Cap | Maximum 20 active listings per player |
| Audit Log | Full transaction history logged |

---

## Economy Balance

### Starting Resources
- **Starting Silver**: 500

### Silver Rewards
| Activity | Silver Range |
|----------|--------------|
| Loot Drops | 10–100 per enemy |
| Strikes | 200–500 per completion |
| Raids | 1,000–5,000 per completion |

---

## Required C++ Components

```cpp
// ATradingHub - In-game location/trigger for trading
// UMarketplaceComponent - Attached to PlayerController
// UMarketplaceWidget - UMG UI for marketplace interface
// USilverTransaction - Tracks all currency movements
```

### ATradingHub
In-game actor placed in hub areas. Players interact to open marketplace UI.

### UMarketplaceComponent
Attached to PlayerController. Manages player's listings, silver balance, and purchase权限.

### UMarketplaceWidget
UMG-based UI showing available listings with filters for type, rarity, and price range.

### USilverTransaction
Data structure and manager for immutable transaction ledger (seller, buyer, amount, timestamp).

---

## Commission Calculation Reference

```cpp
int32 UMarketplaceManager::CalculateCommission(int32 SalePrice)
{
    return FMath::CeilToInt(SalePrice * 0.30f);
}

int32 UMarketplaceManager::CalculateSellerPayout(int32 SalePrice)
{
    // 70% of (SalePrice - ListingFee)
    // Listing fee (10 silver) is refunded on successful sale
    return FMath::FloorToInt((SalePrice - 10) * 0.70f);
}
```

---

*Document Version: 1.0*
*System: Destiny Cyberpunk*
