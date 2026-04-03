#include "Controller/AtomichartsPlayerController.h"
#include "Character/AtomichartsCharacter.h"
#include "Game/AAtomichartsPlayerState.h"

AAtomichartsPlayerController::AAtomichartsPlayerController()
{
    bReplicates = true;
}

void AAtomichartsPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

AAtomichartsPlayerState* AAtomichartsPlayerController::GetAtomichartsPlayerState() const
{
    return Cast<AAtomichartsPlayerState>(PlayerState);
}

AAtomichartsCharacter* AAtomichartsPlayerController::GetAtomichartsCharacter() const
{
    return Cast<AAtomichartsCharacter>(GetPawn());
}

void AAtomichartsPlayerController::ClientMatchEnded_Implementation(int32 WinnerTeam)
{
    // Client-side match end handling (show results screen, etc.)
}
