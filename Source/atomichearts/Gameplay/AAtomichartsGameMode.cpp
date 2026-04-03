#include "Game/AAtomichartsGameMode.h"
#include "Character/AtomichartsCharacter.h"
#include "Controller/AtomichartsPlayerController.h"
#include "Game/AAtomichartsGameState.h"
#include "Game/AtomichartsTypes.h"
#include "Kismet/GameplayStatics.h"

AAtomichartsGameMode::AAtomichartsGameMode()
{
    GameStateClass = AAtomichartsGameState::StaticClass();
    PlayerStateClass = AAtomichartsPlayerState::StaticClass();
    bDelayedStart = true;
}

void AAtomichartsGameMode::StartMatch()
{
    Super::StartMatch();

    if (AAtomichartsGameState* GS = GetGameState<AAtomichartsGameState>())
    {
        GS->MatchDuration = MatchDuration;
        GS->StartMatch();
    }
}

void AAtomichartsGameMode::EndMatch()
{
    if (AAtomichartsGameState* GS = GetGameState<AAtomichartsGameState>())
    {
        GS->EndMatch();
    }
}

bool AAtomichartsGameMode::IsMatchActive() const
{
    if (const AAtomichartsGameState* GS = GetGameState<AAtomichartsGameState>())
    {
        return GS->MatchState == EMatchState::InProgress;
    }
    return false;
}

void AAtomichartsGameMode::PlayerEliminated(AAtomichartsCharacter* EliminatedCharacter,
                                             AAtomichartsPlayerController* VictimController,
                                             AAtomichartsPlayerController* Attacker)
{
    if (!EliminatedCharacter || !VictimController)
        return;

    // Attacker gets kill
    if (Attacker && Attacker != VictimController)
    {
        if (AAtomichartsPlayerState* AttackerPS = Attacker->GetPlayerState<AAtomichartsPlayerState>())
        {
            AttackerPS->AddKill();

            // Team score
            if (AAtomichartsGameState* GS = GetGameState<AAtomichartsGameState>())
            {
                GS->AddTeamScore(AttackerPS->TeamID, 1);
            }
        }
    }

    // Victim death
    if (AAtomichartsPlayerState* VictimPS = VictimController->GetPlayerState<AAtomichartsPlayerState>())
    {
        VictimPS->AddDeath();
    }

    // Respawn
    FTimerHandle RespawnHandle;
    GetWorldTimerManager().SetTimer(RespawnHandle, [this, VictimController]()
    {
        RespawnPlayer(VictimController);
    }, RespawnDelay, false);

    CheckMatchEnd();
}

void AAtomichartsGameMode::RespawnPlayer(AAtomichartsPlayerController* PlayerController)
{
    if (!PlayerController)
        return;

    FVector SpawnLocation = FVector::ZeroVector;
    FRotator SpawnRotation = FRotator::ZeroRotator;

    if (APlayerStart* BestStart = FindPlayerStart(PlayerController, TEXT("Player")))
    {
        SpawnLocation = BestStart->GetActorLocation();
        SpawnRotation = BestStart->GetActorRotation();
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = PlayerController;

    if (AAtomichartsCharacter* NewCharacter = GetWorld()->SpawnActor<AAtomichartsCharacter>(
        AAtomichartsCharacter::StaticClass(),
        SpawnLocation,
        SpawnRotation,
        SpawnParams))
    {
        PlayerController->Possess(NewCharacter);
    }
}

void AAtomichartsGameMode::CheckMatchEnd()
{
    if (AAtomichartsGameState* GS = GetGameState<AAtomichartsGameState>())
    {
        if (GS->RedTeamScore >= ScoreToWin || GS->BlueTeamScore >= ScoreToWin)
        {
            EndMatch();
        }
    }
}
