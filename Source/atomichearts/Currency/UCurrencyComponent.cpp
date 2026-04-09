// Copyright 2026 Atomic Hearts Team
#include "Currency/UCurrencyComponent.h"
#include "Marketplace/UMarketplaceManager.h"
#include "Kismet/KismetMathLibrary.h"

UCurrencyComponent::UCurrencyComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UCurrencyComponent::SetOwnerPlayerID(int64 InPlayerID) {
    OwnerPlayerID = InPlayerID;
    UE_LOG(LogTemp, Log, TEXT("CurrencyComponent: OwnerPlayerID set to %lld"), OwnerPlayerID);
}

void UCurrencyComponent::SetMarketplaceManager(UMarketplaceManager* InMarketplace) {
    Marketplace = InMarketplace;
    if (Marketplace) {
        UE_LOG(LogTemp, Log, TEXT("CurrencyComponent: MarketplaceManager set, binding events"));
        BindToMarketplace();
    } else {
        UE_LOG(LogTemp, Warning, TEXT("CurrencyComponent: MarketplaceManager is null"));
    }
}

void UCurrencyComponent::BeginPlay() {
    Super::BeginPlay();
    Balance = StartingBalance;
    UE_LOG(LogTemp, Log, TEXT("CurrencyComponent initialized: OwnerPlayerID=%lld Balance=%d"), OwnerPlayerID, Balance);
}

void UCurrencyComponent::BindToMarketplace() {
    if (!Marketplace) {
        UE_LOG(LogTemp, Warning, TEXT("BindToMarketplace: Marketplace is null"));
        return;
    }
    // Bind to marketplace's OnItemSold event
    Marketplace->OnItemSold.AddDynamic(this, &UCurrencyComponent::OnMarketplacePurchase);
    UE_LOG(LogTemp, Log, TEXT("CurrencyComponent: Bound to Marketplace OnItemSold"));
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

    // Broadcast player-scoped event only if this component belongs to buyer or seller
    if (OwnerPlayerID == BuyerID || OwnerPlayerID == SellerID) {
        OnItemPurchased.Broadcast(SellerID, BuyerID, ItemID, Price, Payout);
        // Also broadcast local version (same for now)
        OnLocalItemPurchased.Broadcast(SellerID, BuyerID, ItemID, Price, Payout);
    }
    
    UE_LOG(LogTemp, Log,
        TEXT("Purchase settled: Buyer=%lld Seller=%lld Item=%s Price=%d Payout=%d Commission=%d OwnerPlayerID=%lld"),
        BuyerID, SellerID, *ItemID, Price, Payout, Commission, OwnerPlayerID);
}
