// Copyright 2026 Atomic Hearts Team
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UCurrencyComponent.generated.h"

class UMarketplaceManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCurrencyChanged, int64, PlayerID, int32, OldBalance, int32, NewBalance, int32, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPurchaseFailed, int64, PlayerID, const FString&, Reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnItemPurchased, int64, SellerID, int64, BuyerID, const FString&, ItemID, int32, Price, int32, Payout);

UCLASS(ClassGroup=(Atomichearts), meta=(BlueprintSpawnableComponent))
class ATOMICHEARTS_API UCurrencyComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UCurrencyComponent();

    UFUNCTION(BlueprintPure)
    int32 GetBalance() const { return Balance; }

    UFUNCTION(BlueprintCallable)
    bool CanAfford(int32 Amount) const { return Balance >= Amount; }

    UFUNCTION(BlueprintCallable)
    void AddCurrency(int32 Amount, int64 PlayerID);

    UFUNCTION(BlueprintCallable)
    bool RemoveCurrency(int32 Amount, int64 PlayerID);

    /** Called by marketplace when a purchase completes */
    UFUNCTION(BlueprintCallable)
    void OnMarketplacePurchase(int64 SellerID, int64 BuyerID, const FString& ItemID,
                                int32 Price, int32 Payout, int32 Commission);

    UPROPERTY(BlueprintAssignable)
    FOnCurrencyChanged OnCurrencyChanged;

    UPROPERTY(BlueprintAssignable)
    FOnPurchaseFailed OnPurchaseFailed;

    UPROPERTY(BlueprintAssignable)
    FOnItemPurchased OnItemPurchased;

protected:
    void BeginPlay() override;

    /** Bind to marketplace events */
    void BindToMarketplace();

    UPROPERTY(EditDefaultsOnly, Category="Currency")
    int32 StartingBalance = 1000;

    UPROPERTY(EditAnywhere, Category="Currency")
    int32 Balance = 1000;

    UPROPERTY()
    int64 OwnerPlayerID = 0;

    UPROPERTY()
    UMarketplaceManager* Marketplace = nullptr;
};
