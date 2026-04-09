#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Game/AtomichartsTypes.h"
#include "AAtomichartsGameMode.generated.h"

class AAtomichartsCharacter;
class AAtomichartsPlayerController;
class AAtomichartsPlayerState;
class UCurrencyComponent;
class UMarketplaceManager;

UCLASS()
class ATOMICHEARTS_API AAtomichartsGameMode : public AGameMode
{
    GENERATED_BODY()

public:
    AAtomichartsGameMode();

    virtual void PlayerEliminated(AAtomichartsCharacter* EliminatedCharacter,
                                   AAtomichartsPlayerController* VictimController,
                                   AAtomichartsPlayerController* Attacker);

    virtual void RespawnPlayer(AAtomichartsPlayerController* PlayerController);

    UFUNCTION(BlueprintCallable, Category = "Match")
    virtual void StartMatch() override;

    UFUNCTION(BlueprintCallable, Category = "Match")
    virtual void EndMatch() override;

    UFUNCTION(BlueprintPure, Category = "Match")
    bool IsMatchActive() const;

    /** Returns true if this game mode is a PvE Strike mode (wave‑based) */
    UFUNCTION(BlueprintPure, Category = "Match")
    virtual bool IsStrikeMode() const { return false; }

protected:
    virtual void PostLogin(APlayerController* NewPlayer) override;
    
    void WirePlayerMarketplace(AAtomichartsPlayerState* PlayerState);

    UPROPERTY(EditAnywhere, Category = "Respawn")
    float RespawnDelay = 5.f;

    UPROPERTY(EditAnywhere, Category = "Match")
    int32 ScoreToWin = 100;

    UPROPERTY(EditAnywhere, Category = "Match")
    float MatchDuration = 600.f;

    virtual void CheckMatchEnd();
};
