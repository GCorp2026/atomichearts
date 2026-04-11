// Copyright 2024 Atomichearts. All rights reserved.
#include "HealingEffect.h"
#include "Gameplay/UAtomicHeartsAttributeSet.h"

UHealingEffect::UHealingEffect()
{
    DurationPolicy = EGameplayEffectDurationType::HasDuration;
    DurationMagnitude = FScalableFloat(1.0f);
    PeriodicInterval = 1.0f;
    bExecutePeriodicEffectOnApplication = true;

    // Modifier: +HealingAmount to Health per tick
    FGameplayModifierInfo HealMod;
    HealMod.ModifierMagnitude = FScalableFloat(0.0f); // overridden at runtime via SetByCaller
    HealMod.ModifierOp = EGameplayModOp::Additive;
    HealMod.Attribute = UAtomicHeartsAttributeSet::GetHealthAttribute();
    Modifiers.Add(HealMod);
}
