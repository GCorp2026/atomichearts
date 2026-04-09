# Marketplace Fixes — 2026-04-09 (Updated)

## All 5 Gaps Fixed

### 1. HasItem() ✅
`InventoryComponent->HasItem()` wired in `VerifyOwnership()`

### 2. CurrencyManager ✅
`UCurrencyComponent` built — binds to `OnItemSold`, handles gold transfer

### 3. TotalKills++ ✅
`State.TotalKills++` in `AddXP()`

### 4. RarityUpgradePaths ✅
Populated defaults: Common→Uncommon(5k), Rare(10k), Epic(20k), Legendary(40k)

### 5. LockItem/UnlockItem ✅
`SetItemLocked()`, `IsItemLocked()` in InventoryComponent

---

## Seller-Side Unlock — Architecture

**Problem:** On purchase, `PurchaseItem` fires on server but only has buyer's `InventoryComponent`. Can't unlock seller's item directly.

**Solution:** `OnSellerItemUnlocked` delegate — fires after sale/cancel with SellerID, ItemID, ListingID, bSold flag.

**Wiring required (Blueprint or C++ GameMode):**
```cpp
// On seller player's component (PlayerState or GameInstance):
MarketplaceManager->OnSellerItemUnlocked.AddDynamic(
    SellerInventoryComponent,
    &UInventoryComponent::SetItemLocked
);
// Second param: use a lambda/bridge that calls SetItemLocked(ItemID, false)
```

**In practice:**
- Server fires `OnSellerItemUnlocked(SellerID, ItemID, ListingID, true)` in `PurchaseItem()`
- Seller's client receives the event and calls `SellerInventory->SetItemLocked(ItemID, false)`
- Item is now unlocked for seller (or removed if sold)

## Delegates Summary
| Delegate | When | Purpose |
|----------|-------|---------|
| `OnItemListed` | Seller lists item | Deduct listing fee |
| `OnItemSold` | Purchase completes | Transfer currency |
| `OnItemPurchased` | CurrencyComponent on purchase | Update balance UI |
| `OnListingCancelled` | Seller cancels | Refund listing fee |
| `OnSellerItemUnlocked` | Sale or cancel | Unlock seller's item |
