#include "StrikeGameMode.h"
#include "Game/AAtomichartsGameState.h"
#include "Variant_Combat/AI/CombatEnemy.h"
#include "UI/StrikeHUDWidget.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

AStrikeGameMode::AStrikeGameMode()
{
    // Default values can be set in header properties
    bDelayedStart = true;
}

void AStrikeGameMode::BeginPlay()
{
    Super::BeginPlay();
}

void AStrikeGameMode::StartMatch()
{
    Super::StartMatch();

    // Reset wave progression
    CurrentWave = 0;
    EnemiesRemaining = 0;
    WaveState = EWaveState::Preparing;

    // Create HUD for all players
    CreateHUD();

    // Start first wave after a short delay
    GetWorld()->GetTimerManager().SetTimer(
        WaveStartTimer,
        this,
        &AStrikeGameMode::StartWave,
        WaveStartDelay
    );
}

void AStrikeGameMode::EndMatch()
{
    // Clean up any remaining enemies
    UnbindEnemyDelegates();
    SpawnedEnemies.Empty();

    // Remove HUD
    RemoveHUD();

    Super::EndMatch();
}

void AStrikeGameMode::StartWave()
{
    if (WaveState == EWaveState::Boss)
    {
        // Already in boss wave, do nothing
        return;
    }

    CurrentWave++;
    UE_LOG(LogTemp, Log, TEXT("Strike: Starting wave %d/%d"), CurrentWave, TotalWaves);

    // Check if this is the final wave
    if (CurrentWave >= TotalWaves)
    {
        StartBossWave();
        return;
    }

    WaveState = EWaveState::InProgress;
    SpawnWaveEnemies();
    UpdateHUD();
}

void AStrikeGameMode::SpawnWaveEnemies()
{
    // Clear previous wave's references
    UnbindEnemyDelegates();
    SpawnedEnemies.Empty();

    // Determine number of enemies for this wave (could be overridden per wave)
    int32 NumEnemies = EnemiesPerWave;
    if (CurrentWave == 1)
    {
        // First wave might have fewer enemies (optional)
        // NumEnemies = FMath::Max(EnemiesPerWave / 2, 1);
    }

    // Spawn enemies
    for (int32 i = 0; i < NumEnemies; ++i)
    {
        TSubclassOf<ACombatEnemy> EnemyClass = GetRandomEnemyClass();
        AActor* SpawnPoint = GetRandomSpawnPoint();

        if (EnemyClass && SpawnPoint)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            ACombatEnemy* Enemy = GetWorld()->SpawnActor<ACombatEnemy>(
                EnemyClass,
                SpawnPoint->GetActorTransform(),
                SpawnParams
            );

            if (Enemy)
            {
                SpawnedEnemies.Add(Enemy);
                BindEnemyDelegates(Enemy);
            }
        }
    }

    EnemiesRemaining = SpawnedEnemies.Num();
    UE_LOG(LogTemp, Log, TEXT("Strike: Spawned %d enemies for wave %d"), EnemiesRemaining, CurrentWave);
}

void AStrikeGameMode::OnEnemyDied()
{
    if (EnemiesRemaining <= 0)
        return;

    EnemiesRemaining--;
    UE_LOG(LogTemp, Log, TEXT("Strike: Enemy died, %d remaining"), EnemiesRemaining);

    UpdateHUD();
    CheckWaveCompletion();
}

void AStrikeGameMode::CompleteWave()
{
    WaveState = EWaveState::Completed;
    UE_LOG(LogTemp, Log, TEXT("Strike: Wave %d completed"), CurrentWave);

    // Prepare next wave after delay
    GetWorld()->GetTimerManager().SetTimer(
        WaveStartTimer,
        this,
        &AStrikeGameMode::StartWave,
        WaveStartDelay
    );
}

void AStrikeGameMode::StartBossWave()
{
    WaveState = EWaveState::Boss;
    UE_LOG(LogTemp, Log, TEXT("Strike: Starting BOSS wave"));

    // Clear previous enemies
    UnbindEnemyDelegates();
    SpawnedEnemies.Empty();

    // Spawn boss
    if (BossEnemyClass)
    {
        AActor* SpawnPoint = GetRandomSpawnPoint();
        if (SpawnPoint)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            ACombatEnemy* Boss = GetWorld()->SpawnActor<ACombatEnemy>(
                BossEnemyClass,
                SpawnPoint->GetActorTransform(),
                SpawnParams
            );

            if (Boss)
            {
                SpawnedEnemies.Add(Boss);
                BindEnemyDelegates(Boss);
                EnemiesRemaining = 1;
            }
        }
    }
    else
    {
        // Fallback: spawn a regular enemy as boss
        UE_LOG(LogTemp, Warning, TEXT("Strike: BossEnemyClass not set, using regular enemy"));
        SpawnWaveEnemies();
    }

    UpdateHUD();
}

void AStrikeGameMode::UpdateHUD()
{
    for (UStrikeHUDWidget* HUD : StrikeHUDs)
    {
        if (HUD)
        {
            HUD->UpdateWaveInfo(CurrentWave, TotalWaves);
            HUD->UpdateEnemiesRemaining(EnemiesRemaining);
            // Optionally update objective text based on wave state
            if (WaveState == EWaveState::Boss)
            {
                HUD->UpdateObjective(FText::FromString(TEXT("Defeat the BOSS!")));
                HUD->SetBossWarningVisible(true);
            }
            else
            {
                HUD->UpdateObjective(FText::FromString(TEXT("Defeat all enemies")));
                HUD->SetBossWarningVisible(false);
            }
        }
    }
}

void AStrikeGameMode::CheckWaveCompletion()
{
    if (EnemiesRemaining <= 0)
    {
        CompleteWave();
    }
}

AActor* AStrikeGameMode::GetRandomSpawnPoint() const
{
    if (SpawnPoints.Num() == 0)
        return nullptr;

    int32 Index = FMath::RandRange(0, SpawnPoints.Num() - 1);
    return SpawnPoints[Index];
}

TSubclassOf<ACombatEnemy> AStrikeGameMode::GetRandomEnemyClass() const
{
    if (EnemyClasses.Num() == 0)
        return nullptr;

    int32 Index = FMath::RandRange(0, EnemyClasses.Num() - 1);
    return EnemyClasses[Index];
}

void AStrikeGameMode::BindEnemyDelegates(ACombatEnemy* Enemy)
{
    if (Enemy)
    {
        Enemy->OnEnemyDied.AddDynamic(this, &AStrikeGameMode::OnEnemyDied);
    }
}

void AStrikeGameMode::UnbindEnemyDelegates()
{
    for (ACombatEnemy* Enemy : SpawnedEnemies)
    {
        if (Enemy)
        {
            Enemy->OnEnemyDied.RemoveDynamic(this, &AStrikeGameMode::OnEnemyDied);
        }
    }
}

void AStrikeGameMode::CreateHUD()
{
    // Clear existing HUDs
    RemoveHUD();

    // Create HUD for each player controller
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = It->Get();
        if (PC && PC->IsLocalPlayerController() && StrikeHUDClass)
        {
            UStrikeHUDWidget* HUD = CreateWidget<UStrikeHUDWidget>(PC, StrikeHUDClass);
            if (HUD)
            {
                HUD->AddToViewport();
                StrikeHUDs.Add(HUD);
            }
        }
    }

    // Initial HUD update
    UpdateHUD();
}

void AStrikeGameMode::RemoveHUD()
{
    for (UStrikeHUDWidget* HUD : StrikeHUDs)
    {
        if (HUD)
        {
            HUD->RemoveFromParent();
        }
    }
    StrikeHUDs.Empty();
}