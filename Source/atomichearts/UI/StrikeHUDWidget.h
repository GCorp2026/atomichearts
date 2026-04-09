#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StrikeHUDWidget.generated.h"

/**
 * HUD widget for Strike game mode.
 */
UCLASS()
class ATOMICHEARTS_API UStrikeHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /** Updates the wave display */
    UFUNCTION(BlueprintCallable, Category = "Strike HUD")
    void UpdateWaveInfo(int32 CurrentWave, int32 TotalWaves);

    /** Updates the enemy remaining count */
    UFUNCTION(BlueprintCallable, Category = "Strike HUD")
    void UpdateEnemiesRemaining(int32 EnemiesRemaining);

    /** Updates the objective text */
    UFUNCTION(BlueprintCallable, Category = "Strike HUD")
    void UpdateObjective(const FText& NewObjective);

    /** Shows/hides the boss warning */
    UFUNCTION(BlueprintCallable, Category = "Strike HUD")
    void SetBossWarningVisible(bool bVisible);

protected:
    /** Blueprint‑implementable events for UI updates */
    UFUNCTION(BlueprintImplementableEvent, Category = "Strike HUD")
    void OnWaveInfoUpdated(int32 CurrentWave, int32 TotalWaves);

    UFUNCTION(BlueprintImplementableEvent, Category = "Strike HUD")
    void OnEnemiesRemainingUpdated(int32 EnemiesRemaining);

    UFUNCTION(BlueprintImplementableEvent, Category = "Strike HUD")
    void OnObjectiveUpdated(const FText& NewObjective);

    UFUNCTION(BlueprintImplementableEvent, Category = "Strike HUD")
    void OnBossWarningToggled(bool bVisible);
};