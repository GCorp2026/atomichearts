// Copyright 2024 Atomichearts. All rights reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "AmmoConsumptionEffect.generated.h"

/**
 * Gameplay effect that reduces CurrentAmmo by 1.
 * Used by weapon firing to consume ammo via GAS.
 */
UCLASS()
class ATOMICHEARTS_API UAmmoConsumptionEffect : public UGameplayEffect
{
    GENERATED_BODY()
public:
    UAmmoConsumptionEffect();
};