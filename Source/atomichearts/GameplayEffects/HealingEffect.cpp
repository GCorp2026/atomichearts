// Copyright 2024 Atomichearts. All rights reserved.
#include "HealingEffect.h"

UHealingEffect::UHealingEffect()
{
    DurationPolicy = EGameplayEffectDurationType::HasDuration;
    // Duration is set dynamically (equals the desired regen duration)
    DurationMagnitude = FScalableFloat(1.0f);
    
    // Periodic tick every second
    PeriodicInterval = 1.0f;
    bExecutePeriodicEffectOnApplication = true;
    
    // Modifier: +RegenRate healing per tick (magnitude set dynamically)
    FGameplayModifierInfo& HealMod = ModifyMagnitude.AddEDamageModifier(EGameplayModOp::Additive);
    HealMod.ModifierName = FGameplayModifierOps::Additive;
    // Magnitude set dynamically when applying
    HealMod.ModifierMagnitude = FScalableFloat(0.0f); // placeholder, overridden at runtime
}