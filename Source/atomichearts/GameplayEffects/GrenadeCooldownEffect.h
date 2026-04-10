// Copyright 2024 Atomichearts. All rights reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GrenadeCooldownEffect.generated.h"

/**
 * Gameplay effect applied when a grenade is on cooldown.
 * Duration equals the cooldown time.
 */
UCLASS()
class ATOMICHEARTS_API UGrenadeCooldownEffect : public UGameplayEffect
{
    GENERATED_BODY()
public:
    UGrenadeCooldownEffect();
};