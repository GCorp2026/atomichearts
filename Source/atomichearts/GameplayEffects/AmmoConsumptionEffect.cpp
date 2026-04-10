// Copyright 2024 Atomichearts. All rights reserved.
#include "AmmoConsumptionEffect.h"

UAmmoConsumptionEffect::UAmmoConsumptionEffect()
{
    // Instant effect: modifier modifies CurrentAmmo by -1
    FGameplayModifierInfo& AmmoMod = ModifyMagnitude.AddEDamageModifier(EGameplayModOp::Additive);
    AmmoMod.ModifierName = FGameplayModifierOps::Additive;
    AmmoMod.ModifierMagnitude = FScalableFloat(-1.0f);
    
    bExecutePeriodicEffectOnApplication = true;
    DurationPolicy = EGameplayEffectDurationType::Instant;
}