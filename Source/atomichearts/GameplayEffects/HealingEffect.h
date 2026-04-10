// Copyright 2024 Atomichearts. All rights reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "HealingEffect.generated.h"

/**
 * Gameplay effect for health regeneration.
 * Applies a periodic heal over time based on RegenRate.
 */
UCLASS()
class ATOMICHEARTS_API UHealingEffect : public UGameplayEffect
{
    GENERATED_BODY()
public:
    UHealingEffect();
};