#include "StrikeHUDWidget.h"

void UStrikeHUDWidget::UpdateWaveInfo(int32 CurrentWave, int32 TotalWaves)
{
    OnWaveInfoUpdated(CurrentWave, TotalWaves);
}

void UStrikeHUDWidget::UpdateEnemiesRemaining(int32 EnemiesRemaining)
{
    OnEnemiesRemainingUpdated(EnemiesRemaining);
}

void UStrikeHUDWidget::UpdateObjective(const FText& NewObjective)
{
    OnObjectiveUpdated(NewObjective);
}

void UStrikeHUDWidget::SetBossWarningVisible(bool bVisible)
{
    OnBossWarningToggled(bVisible);
}