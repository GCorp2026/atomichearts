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
    Currency.SetBaseValue(0.0f);
    Currency.SetCurrentValue(0.0f);
    
    // Weapon Attributes defaults
    CurrentAmmo.SetBaseValue(30.0f);
    CurrentAmmo.SetCurrentValue(30.0f);
    MaxAmmo.SetBaseValue(30.0f);
    MaxAmmo.SetCurrentValue(30.0f);
    ReloadSpeed.SetBaseValue(1.0f);
    ReloadSpeed.SetCurrentValue(1.0f);
    FireRate.SetBaseValue(0.25f);
    FireRate.SetCurrentValue(0.25f);
    
    // Stamina, Energy, MoveSpeed defaults
    Stamina.SetBaseValue(100.0f);
    Stamina.SetCurrentValue(100.0f);
    Energy.SetBaseValue(100.0f);
    Energy.SetCurrentValue(100.0f);
    MoveSpeed.SetBaseValue(600.0f);
    MoveSpeed.SetCurrentValue(600.0f);
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
    else if (Attribute == GetCurrencyAttribute())
    {
        NewValue = FMath::Max(NewValue, 0.0f);
    }
    else if (Attribute == GetCurrentAmmoAttribute())
    {
        // Clamp ammo between 0 and MaxAmmo
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxAmmo());
    }
    else if (Attribute == GetMaxAmmoAttribute())
    {
        // MaxAmmo must be >= 0
        NewValue = FMath::Max(NewValue, 0.0f);
        // If CurrentAmmo exceeds new Max, clamp later in PostGameplayEffectExecute
    }
    else if (Attribute == GetReloadSpeedAttribute())
    {
        // ReloadSpeed must be positive (minimum epsilon)
        NewValue = FMath::Max(NewValue, 0.01f);
    }
    else if (Attribute == GetFireRateAttribute())
    {
        // FireRate as seconds between shots, must be positive
        NewValue = FMath::Max(NewValue, 0.01f);
    }
    else if (Attribute == GetStaminaAttribute())
    {
        // Stamina must be non-negative
        NewValue = FMath::Max(NewValue, 0.0f);
    }
    else if (Attribute == GetEnergyAttribute())
    {
        // Energy must be non-negative
        NewValue = FMath::Max(NewValue, 0.0f);
    }
    else if (Attribute == GetMoveSpeedAttribute())
    {
        // MoveSpeed must be positive (minimum epsilon)
        NewValue = FMath::Max(NewValue, 1.0f);
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
    else if (Data.EvaluatedData.Attribute == GetCurrentAmmoAttribute())
    {
        SetCurrentAmmo(FMath::Clamp(GetCurrentAmmo(), 0.0f, GetMaxAmmo()));
    }
    else if (Data.EvaluatedData.Attribute == GetMaxAmmoAttribute())
    {
        // Ensure MaxAmmo >= 0
        SetMaxAmmo(FMath::Max(GetMaxAmmo(), 0.0f));
        // Clamp CurrentAmmo to new Max
        SetCurrentAmmo(FMath::Clamp(GetCurrentAmmo(), 0.0f, GetMaxAmmo()));
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
    DOREPLIFETIME_CONDITION_NOTIFY(UAtomicHeartsAttributeSet, Currency, COND_None, REPNOTIFY_Always);
    // Weapon attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UAtomicHeartsAttributeSet, CurrentAmmo, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAtomicHeartsAttributeSet, MaxAmmo, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAtomicHeartsAttributeSet, ReloadSpeed, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAtomicHeartsAttributeSet, FireRate, COND_None, REPNOTIFY_Always);
    // Movement/Resource attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UAtomicHeartsAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAtomicHeartsAttributeSet, Energy, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAtomicHeartsAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
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
void UAtomicHeartsAttributeSet::OnRep_Currency(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAtomicHeartsAttributeSet, Currency, OldValue);
}

void UAtomicHeartsAttributeSet::OnRep_CurrentAmmo(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAtomicHeartsAttributeSet, CurrentAmmo, OldValue);
}

void UAtomicHeartsAttributeSet::OnRep_MaxAmmo(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAtomicHeartsAttributeSet, MaxAmmo, OldValue);
}

void UAtomicHeartsAttributeSet::OnRep_ReloadSpeed(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAtomicHeartsAttributeSet, ReloadSpeed, OldValue);
}

void UAtomicHeartsAttributeSet::OnRep_FireRate(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAtomicHeartsAttributeSet, FireRate, OldValue);
}

void UAtomicHeartsAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAtomicHeartsAttributeSet, Stamina, OldValue);
}

void UAtomicHeartsAttributeSet::OnRep_Energy(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAtomicHeartsAttributeSet, Energy, OldValue);
}

void UAtomicHeartsAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAtomicHeartsAttributeSet, MoveSpeed, OldValue);
}
