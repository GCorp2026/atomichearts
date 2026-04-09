#include "Game/AAtomichartsGameMode.h"
#include "Character/AtomichartsCharacter.h"
#include "Controller/AtomichartsPlayerController.h"
#include "Game/AAtomichartsGameState.h"
#include "Game/AAtomichartsPlayerState.h"
#include "Currency/UCurrencyComponent.h"
#include "Marketplace/UMarketplaceManager.h"
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

void AAtomichartsGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    
    if (AAtomichartsPlayerState* PlayerState = NewPlayer->GetPlayerState<AAtomichartsPlayerState>())
    {
        WirePlayerMarketplace(PlayerState);
    }
}

void AAtomichartsGameMode::WirePlayerMarketplace(AAtomichartsPlayerState* PlayerState)
{
    if (!PlayerState)
    {
        UE_LOG(LogTemp, Warning, TEXT("WirePlayerMarketplace: PlayerState is null"));
        return;
    }
    
    // Get marketplace manager from game state
    if (AAtomichartsGameState* GameState = GetGameState<AAtomichartsGameState>())
    {
        if (UMarketplaceManager* Marketplace = GameState->GetMarketplaceManager())
        {
            // Wire currency component
            if (PlayerState->CurrencyComponent)
            {
                PlayerState->CurrencyComponent->SetOwnerPlayerID(PlayerState->GetPlayerId());
                PlayerState->CurrencyComponent->SetMarketplaceManager(Marketplace);
                UE_LOG(LogTemp, Log, TEXT("WirePlayerMarketplace: CurrencyComponent for player %d wired"), PlayerState->GetPlayerId());
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("WirePlayerMarketplace: CurrencyComponent is null"));
            }
            
            // Wire inventory component
            if (PlayerState->InventoryComponent)
            {
                PlayerState->InventoryComponent->SetOwnerPlayerID(PlayerState->GetPlayerId());
                PlayerState->InventoryComponent->SetMarketplaceManager(Marketplace);
                UE_LOG(LogTemp, Log, TEXT("WirePlayerMarketplace: InventoryComponent for player %d wired"), PlayerState->GetPlayerId());
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("WirePlayerMarketplace: InventoryComponent is null"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("WirePlayerMarketplace: MarketplaceManager is null"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("WirePlayerMarketplace: GameState is null"));
    }
}
