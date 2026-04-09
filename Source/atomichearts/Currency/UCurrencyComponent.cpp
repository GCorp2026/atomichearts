// Copyright 2026 Atomic Hearts Team
#include "Currency/UCurrencyComponent.h"
#include "Marketplace/UMarketplaceManager.h"
#include "Kismet/KismetMathLibrary.h"

UCurrencyComponent::UCurrencyComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UCurrencyComponent::BeginPlay() {
    Super::BeginPlay();
    OwnerPlayerID = 0; // Set from owning player state
    Balance = StartingBalance;
    UE_LOG(LogTemp, Log, TEXT("CurrencyComponent initialized: Balance=%d"), Balance);
}

void UCurrencyComponent::BindToMarketplace() {
    if (!Marketplace) return;
    // Note: In Blueprint or GameInstance, wire:
    // Marketplace->OnItemSold.AddDynamic(this, &UCurrencyComponent::OnMarketplacePurchase);
}

void UCurrencyComponent::AddCurrency(int32 Amount, int64 PlayerID) {
    if (Amount <= 0) return;
    int32 Old = Balance;
    Balance += Amount;
    OnCurrencyChanged.Broadcast(PlayerID, Old, Balance, Amount);
    UE_LOG(LogTemp, Log, TEXT("AddCurrency: +%d -> %d"), Amount, Balance);
}

bool UCurrencyComponent::RemoveCurrency(int32 Amount, int64 PlayerID) {
    if (Amount <= 0) return false;
    if (!CanAfford(Amount)) {
        OnPurchaseFailed.Broadcast(PlayerID, TEXT("Insufficient funds"));
        return false;
    }
    int32 Old = Balance;
    Balance -= Amount;
    OnCurrencyChanged.Broadcast(PlayerID, Old, Balance, -Amount);
    UE_LOG(LogTemp, Log, TEXT("RemoveCurrency: -%d -> %d"), Amount, Balance);
    return true;
}

void UCurrencyComponent::OnMarketplacePurchase(int64 SellerID, int64 BuyerID,
                                               const FString& ItemID,
                                               int32 Price, int32 Payout, int32 Commission) {
    if (BuyerID == OwnerPlayerID) {
        // We're the buyer — deduct price
        if (!RemoveCurrency(Price, BuyerID)) {
            UE_LOG(LogTemp, Warning, TEXT("Purchase failed: Buyer %lld cannot afford %d"), BuyerID, Price);
            OnPurchaseFailed.Broadcast(BuyerID, TEXT("Insufficient funds"));
            return;
        }
    }

    if (SellerID == OwnerPlayerID) {
        // We're the seller — add payout (commission already deducted by marketplace math)
        AddCurrency(Payout, SellerID);
    }

    OnItemPurchased.Broadcast(SellerID, BuyerID, ItemID, Price, Payout);
    UE_LOG(LogTemp, Log,
        TEXT("Purchase settled: Buyer=%lld Seller=%lld Item=%s Price=%d Payout=%d Commission=%d"),
        BuyerID, SellerID, *ItemID, Price, Payout, Commission);
}
