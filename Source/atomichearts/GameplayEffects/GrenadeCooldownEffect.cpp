// Copyright 2024 Atomichearts. All rights reserved.
#include "GrenadeCooldownEffect.h"

UGrenadeCooldownEffect::UGrenadeCooldownEffect()
{
    DurationPolicy = EGameplayEffectDurationType::HasDuration;
    DurationMagnitude = FScalableFloat(3.0f); // default 3 seconds
    bExecutePeriodicEffectOnApplication = false;
}