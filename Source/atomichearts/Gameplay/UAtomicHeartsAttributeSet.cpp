// Copyright (c) 2026 Atomic Hearts Team. All rights reserved.

#include "UAtomicHeartsAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"

UAtomicHeartsAttributeSet::UAtomicHeartsAttributeSet()
{
    // Initialize default values
    Health.SetBaseValue(100.0f);
    Health.SetCurrentValue(100.0f);
    MaxHealth.SetBaseValue(100.0f);
    MaxHealth.SetCurrentValue(100.0f);
    Shield.SetBaseValue(50.0f);
    Shield.SetCurrentValue(50.0f);
    Armor.SetBaseValue(0.0f);
    Armor.SetCurrentValue(0.0f);
    DamageResistance.SetBaseValue(0.0f);
    DamageResistance.SetCurrentValue(0.0f);
}

void UAtomicHeartsAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    // Clamp Health to MaxHealth
    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
    }
    else if (Attribute == GetShieldAttribute())
    {
        // Shield could have its own max, but for simplicity clamp to a large number
        NewValue = FMath::Max(NewValue, 0.0f);
    }
    else if (Attribute == GetArmorAttribute())
    {
        NewValue = FMath::Max(NewValue, 0.0f);
    }
    else if (Attribute == GetDamageResistanceAttribute())
    {
        // DamageResistance as percentage (0-1)
        NewValue = FMath::Clamp(NewValue, 0.0f, 1.0f);
    }
}

void UAtomicHeartsAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    // Handle damage/healing calculations here if needed.
    // For now, just ensure health stays within bounds.
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
    }
    else if (Data.EvaluatedData.Attribute == GetShieldAttribute())
    {
        SetShield(FMath::Max(GetShield(), 0.0f));
    }
}

void UAtomicHeartsAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Replicate attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UAtomicHeartsAttributeSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAtomicHeartsAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAtomicHeartsAttributeSet, Shield, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAtomicHeartsAttributeSet, Armor, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAtomicHeartsAttributeSet, DamageResistance, COND_None, REPNOTIFY_Always);
}

void UAtomicHeartsAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAtomicHeartsAttributeSet, Health, OldValue);
}

void UAtomicHeartsAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAtomicHeartsAttributeSet, MaxHealth, OldValue);
}

void UAtomicHeartsAttributeSet::OnRep_Shield(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAtomicHeartsAttributeSet, Shield, OldValue);
}

void UAtomicHeartsAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAtomicHeartsAttributeSet, Armor, OldValue);
}

void UAtomicHeartsAttributeSet::OnRep_DamageResistance(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAtomicHeartsAttributeSet, DamageResistance, OldValue);
}