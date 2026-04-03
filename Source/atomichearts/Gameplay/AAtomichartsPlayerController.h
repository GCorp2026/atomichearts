#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Game/AtomichartsTypes.h"
#include "AAtomichartsPlayerController.generated.h"

class AAtomichartsCharacter;
class AAtomichartsPlayerState;

UCLASS()
class ATOMICHEARTS_API AAtomichartsPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AAtomichartsPlayerController();

    UFUNCTION(Client, Reliable)
    void ClientMatchEnded(int32 WinnerTeam);

    UFUNCTION(BlueprintPure, Category = "State")
    AAtomichartsPlayerState* GetAtomichartsPlayerState() const;

    UFUNCTION(BlueprintPure, Category = "State")
    AAtomichartsCharacter* GetAtomichartsCharacter() const;

protected:
    virtual void BeginPlay() override;
};
