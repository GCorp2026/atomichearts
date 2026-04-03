#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Game/AtomichartsTypes.h"
#include "AAtomichartsGameState.generated.h"

class AAtomichartsPlayerController;

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

    UFUNCTION(BlueprintCallable, Category = "Match")
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
    UFUNCTION()
    void OnRep_MatchState();

    FTimerHandle MatchTimerHandle;

    UFUNCTION()
    void MatchTimerTick();
};
