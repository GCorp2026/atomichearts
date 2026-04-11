// Copyright 2024 Atomichearts. All rights reserved.
#include "HealingEffect.h"
#include "Gameplay/UAtomicHeartsAttributeSet.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"

UHealingEffect::UHealingEffect()
{
    DurationPolicy = EGameplayEffectDurationType::HasDuration;
    DurationMagnitude = FScalableFloat(1.0f);
    PeriodicInterval = 1.0f;
    bExecutePeriodicEffectOnApplication = true;

    // Modifier: +HealingAmount to Health per tick (SetByCaller)
    FGameplayModifierInfo HealMod;
    FGameplayEffectModifierMagnitude HealMagnitude;
    HealMagnitude.MagnitudeCalculationType = EGameplayEffectMagnitudeCalculation::SetByCaller;
    HealMagnitude.SetByCallerMagnitude.DataName = FName("Healing");
    // DataTag left invalid, we'll use DataName
    HealMod.ModifierMagnitude = HealMagnitude;
    HealMod.ModifierOp = EGameplayModOp::Additive;
    HealMod.Attribute = UAtomicHeartsAttributeSet::GetHealthAttribute();
    Modifiers.Add(HealMod);
}
