# Currency System — 2026-04-09

## Overview
`UCurrencyComponent` handles gold balance for players and integrates with marketplace purchases.

## Files
- `UCurrencyComponent.h` — Component declaration, delegates, interface
- `UCurrencyComponent.cpp` — Implementation

## Architecture

### Delegates
| Delegate | Params | Purpose |
|----------|--------|---------|
| `OnCurrencyChanged` | PlayerID, OldBalance, NewBalance, Delta | UI binding for balance display |
| `OnPurchaseFailed` | PlayerID, Reason | Show "insufficient funds" etc |
| `OnItemPurchased` | SellerID, BuyerID, ItemID, Price, Payout | Log/history tracking |

### Interface
```cpp
GetBalance()            // Current gold
CanAfford(Amount)       // bool check
AddCurrency(Amount)      // Add gold (e.g. quest reward)
RemoveCurrency(Amount)  // Remove gold (returns false if insufficient)
OnMarketplacePurchase()  // Called by marketplace OnItemSold event
```

## Integration with Marketplace
In Blueprint or GameMode:
```
MarketplaceManager.OnItemSold
  → UCurrencyComponent.OnMarketplacePurchase(...)
```

## Wiring Required
```cpp
// In GameMode or PlayerController BeginPlay:
Marketplace->OnItemSold.AddDynamic(CurrencyComponent, &UCurrencyComponent::OnMarketplacePurchase);
```

## TODO
- [ ] Wire `Marketplace->OnItemSold` to `CurrencyComponent->OnMarketplacePurchase` in BP
- [ ] Verify `OwnerPlayerID` is set correctly from owning PlayerState
- [ ] Add initial balance grant on new player creation
