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

## Bugs Fixed (2026-04-09)

| Bug | Fix |
|-----|-----|
| OwnerPlayerID = 0 hardcoded | Added `SetOwnerPlayerID()` method, removed hardcoded 0 |
| Marketplace pointer never assigned | Added `SetMarketplaceManager()` method, auto-binds |
| OnItemPurchased broadcasts to all players | Now only fires if `OwnerPlayerID == BuyerID || OwnerPlayerID == SellerID` |

## New Methods
```cpp
SetOwnerPlayerID(int64 InPlayerID)          // Must be called after spawn
SetMarketplaceManager(UMarketplaceManager*) // Auto-binds to OnItemSold
```

## Updated Wiring
```cpp
// In PlayerState or PlayerController:
CurrencyComponent->SetOwnerPlayerID(PlayerID);
CurrencyComponent->SetMarketplaceManager(MarketplaceManager);
// Marketplace binding happens automatically in SetMarketplaceManager
```

## TODO
- [x] Fix OwnerPlayerID = 0 hardcoded
- [x] Fix Marketplace pointer never assigned
- [x] Fix OnItemPurchased broadcasts to all players
- [ ] Call `SetOwnerPlayerID()` from PlayerState on player login
- [ ] Call `SetMarketplaceManager()` from GameMode/GameInstance
