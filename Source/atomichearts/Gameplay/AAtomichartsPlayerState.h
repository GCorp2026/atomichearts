#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Game/AtomichartsTypes.h"
#include "AAtomichartsPlayerState.generated.h"

class UProgressionComponent;
class UFactionReputationComponent;
class UCurrencyComponent;

UCLASS()
class ATOMICHEARTS_API AAtomichartsPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    AAtomichartsPlayerState();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) override;

    // K/D Stats
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Stats")
    int32 Kills = 0;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Stats")
    int32 Deaths = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    float KDRatio = 0.f;

    // Team
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Team")
    int32 TeamID = 0;

    // Progression
    UPROPERTY(BlueprintReadOnly, Category = "Progression", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UProgressionComponent> ProgressionComponent;

    // Faction Reputation
    UPROPERTY(BlueprintReadOnly, Category = "Faction", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UFactionReputationComponent> FactionReputationComponent;

    // Currency
    UPROPERTY(BlueprintReadOnly, Category = "Currency", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCurrencyComponent> CurrencyComponent;

    // Inventory
    UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInventoryComponent> InventoryComponent;

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddKill();

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddDeath();

    UFUNCTION(BlueprintPure, Category = "Stats")
    int32 GetLightLevel() const;

protected:
    virtual void BeginPlay() override;
};
