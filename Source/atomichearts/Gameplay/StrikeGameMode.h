#pragma once

#include "CoreMinimal.h"
#include "Gameplay/AAtomichartsGameMode.h"
#include "StrikeGameMode.generated.h"

UENUM(BlueprintType)
enum class EWaveState : uint8
{
    Preparing,
    InProgress,
    Completed,
    Boss
};

class UStrikeHUDWidget;

/**
 * Game Mode for cooperative PvE Strikes (wave‑based enemy spawning).
 */
UCLASS()
class ATOMICHEARTS_API AStrikeGameMode : public AAtomichartsGameMode
{
    GENERATED_BODY()

public:
    AStrikeGameMode();

protected:
    virtual void BeginPlay() override;
    virtual void StartMatch() override;
    virtual void EndMatch() override;

public:
    /** Total number of waves (configurable) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strike|Waves", meta = (ClampMin = 1, ClampMax = 20))
    int32 TotalWaves = 5;

    /** Current wave index (1‑based) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Strike|Waves")
    int32 CurrentWave = 0;

    /** Number of enemies still alive in the current wave */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Strike|Waves")
    int32 EnemiesRemaining = 0;

    /** Delay before starting the next wave (seconds) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strike|Waves", meta = (ClampMin = 0.0f, ClampMax = 30.0f))
    float WaveStartDelay = 5.0f;

    /** Current state of the wave */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Strike|Waves")
    EWaveState WaveState = EWaveState::Preparing;

    /** Spawn points for enemies (can be set in editor) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strike|Spawning")
    TArray<AActor*> SpawnPoints;

    /** Enemy classes to spawn (each wave picks randomly) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strike|Spawning")
    TArray<TSubclassOf<class ACombatEnemy>> EnemyClasses;

    /** Boss enemy class for final wave */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strike|Boss")
    TSubclassOf<class ACombatEnemy> BossEnemyClass;

    /** Number of enemies per wave (can be overridden per wave) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strike|Spawning", meta = (ClampMin = 1, ClampMax = 30))
    int32 EnemiesPerWave = 8;

    /** HUD widget class to display wave info */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strike|UI")
    TSubclassOf<UStrikeHUDWidget> StrikeHUDClass;

    /** Start the next wave (callable from Blueprint) */
    UFUNCTION(BlueprintCallable, Category = "Strike|Waves")
    void StartWave();

    /** Spawn enemies for the current wave */
    UFUNCTION(BlueprintCallable, Category = "Strike|Spawning")
    void SpawnWaveEnemies();

    /** Called when an enemy dies (bound to enemy delegate) */
    UFUNCTION()
    void OnEnemyDied();

    /** Complete the current wave and prepare the next */
    UFUNCTION(BlueprintCallable, Category = "Strike|Waves")
    void CompleteWave();

    /** Start the final boss wave */
    UFUNCTION(BlueprintCallable, Category = "Strike|Boss")
    void StartBossWave();

    /** Override to identify as Strike mode */
    virtual bool IsStrikeMode() const override { return true; }

    /** Update HUD for all players */
    void UpdateHUD();

    /** Check if all enemies are dead and wave can be completed */
    void CheckWaveCompletion();

    /** Get a random spawn point from the SpawnPoints array */
    AActor* GetRandomSpawnPoint() const;

    /** Get a random enemy class from EnemyClasses */
    TSubclassOf<ACombatEnemy> GetRandomEnemyClass() const;

protected:
    /** Timer handle for wave start delay */
    FTimerHandle WaveStartTimer;

    /** Array of spawned enemy actors for the current wave */
    TArray<ACombatEnemy*> SpawnedEnemies;

    /** HUD widget instances per player controller */
    TArray<UStrikeHUDWidget*> StrikeHUDs;

    /** Bind to enemy death delegates */
    void BindEnemyDelegates(ACombatEnemy* Enemy);

    /** Unbind from all spawned enemies */
    void UnbindEnemyDelegates();

    /** Create HUD widgets for all players */
    void CreateHUD();

    /** Remove HUD widgets */
    void RemoveHUD();
};