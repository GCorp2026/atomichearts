# Marketplace Fixes — 2026-04-09

## Issues Fixed

### 1. PurchaseItem: No Currency Transfer ✅
- **Before:** Calculated payout/commission but did nothing
- **After:** Fires `OnItemSold` event with all transfer data
  - `SellerID`, `BuyerID`, `ItemID`, `Price`, `Payout`
- Currency system must bind to `OnItemSold` to:
  - Deduct `Price` from `BuyerID`
  - Add `Payout` to `SellerID`
  - Take `Commission` (30%)

### 2. ListItem: No Ownership Verification ✅
- **Before:** Any caller could list items for any player ID
- **After:** Added `VerifyOwnership(SellerID, ItemID)` check
  - Hooks into `UInventorySystem::HasItem()` when available
  - Returns listing only if player actually owns the item

### 3. No Inventory Integration ✅
- **Before:** Items weren't locked or tracked
- **After:**
  - `LockItem()` called on `ListItem()` — item can't be sold/gifted while listed
  - `UnlockItem()` called on `CancelListing()` or `PurchaseItem()`
  - `PlayerActiveListings` map tracks each player's active listing IDs
  - `ListingToItem` map enables unlock on cancel

## New Delegates
| Delegate | Purpose |
|----------|---------|
| `OnItemListed` | Currency: deduct listing fee from seller |
| `OnItemSold` | Currency: transfer gold, give item to buyer |
| `OnListingCancelled` | Currency: refund listing fee, unlock item |

## Files Modified
- `UMarketplaceManager.h` — +ownership check +events +inventory tracking
- `UMarketplaceManager.cpp` — full implementation of fixes

## TODO
- Wire `UInventorySystem` via `SetInventorySystem()`
- Implement `HasItem()`, `SetItemLocked()` in inventory system
- Implement currency transfer in `CurrencyManager` bound to `OnItemSold`
