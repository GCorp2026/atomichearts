#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Game/AtomichartsTypes.h"
#include "AAtomichartsGameState.generated.h"

class AAtomichartsPlayerController;
class UMarketplaceManager;

UCLASS()
class ATOMICHEARTS_API AAtomichartsGameState : public AGameState
{
    GENERATED_BODY()

public:
    AAtomichartsGameState();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) override;

    // Match State
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Match")
    EMatchState MatchState = EMatchState::Waiting;

    // Team Scores
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Score")
    int32 RedTeamScore = 0;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Score")
    int32 BlueTeamScore = 0;

    // Match Timer
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Match")
    float MatchTimeRemaining = 600.f;

    UPROPERTY(EditAnywhere, Category = "Match")
    float MatchDuration = 600.f;

    // Activity Type
    UPROPERTY(EditAnywhere, Category = "Match")
    EActivityType ActivityType = EActivityType::Patrol;

    // Marketplace
    UPROPERTY(BlueprintReadOnly, Category = "Marketplace")
    TObjectPtr<UMarketplaceManager> MarketplaceManager;

    // House Account for marketplace commission
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Marketplace")
    int32 HouseBalance = 0;

    UFUNCTION(BlueprintCallable, Category = "Marketplace")
    int32 GetHouseBalance() const { return HouseBalance; }

    UFUNCTION(BlueprintCallable, Category = "Marketplace")
    void AddHouseBalance(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Marketplace")
    bool WithdrawHouseBalance(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Marketplace")
    UMarketplaceManager* GetMarketplaceManager() const { return MarketplaceManager; }
    void StartMatch();

    UFUNCTION(BlueprintCallable, Category = "Match")
    void EndMatch();

    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddTeamScore(int32 Team, int32 Points);

    UFUNCTION(BlueprintPure, Category = "Match")
    FText GetMatchTimeText() const;

    UFUNCTION(BlueprintPure, Category = "Score")
    int32 GetLeadingTeam() const;

protected:
    virtual void BeginPlay() override;
    UFUNCTION()
    void OnRep_MatchState();

    void BindMarketplaceEvents();
    UFUNCTION()
    void OnMarketplaceItemSold(int64 SellerID, int64 BuyerID, const FString& ItemID, int32 Price, int32 Payout, int32 Commission);

    FTimerHandle MatchTimerHandle;

    UFUNCTION()
    void MatchTimerTick();
};
