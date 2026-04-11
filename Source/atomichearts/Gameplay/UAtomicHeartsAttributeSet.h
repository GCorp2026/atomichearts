// Copyright (c) 2026 Atomic Hearts Team. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "UAtomicHeartsAttributeSet.generated.h"

/**
 * Attribute set for Atomic Hearts characters using Gameplay Ability System.
 * Contains Health, MaxHealth, Shield, Armor, DamageResistance, Currency, and weapon attributes.
 */
UCLASS()
class ATOMICHEARTS_API UAtomicHeartsAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UAtomicHeartsAttributeSet();

    // Attribute Set Overrides
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // Health
    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS_BASIC(UAtomicHeartsAttributeSet, Health);

    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS_BASIC(UAtomicHeartsAttributeSet, MaxHealth);

    // Shield
    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Shield)
    FGameplayAttributeData Shield;
    ATTRIBUTE_ACCESSORS_BASIC(UAtomicHeartsAttributeSet, Shield);

    // Armor (damage reduction)
    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Armor)
    FGameplayAttributeData Armor;
    ATTRIBUTE_ACCESSORS_BASIC(UAtomicHeartsAttributeSet, Armor);

    // DamageResistance (percentage reduction)
    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_DamageResistance)
    FGameplayAttributeData DamageResistance;
    ATTRIBUTE_ACCESSORS_BASIC(UAtomicHeartsAttributeSet, DamageResistance);

    // Currency (in-game money)
    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Currency)
    FGameplayAttributeData Currency;
    ATTRIBUTE_ACCESSORS_BASIC(UAtomicHeartsAttributeSet, Currency);

    // Weapon Attributes
    // CurrentAmmo (ammo in current magazine)
    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_CurrentAmmo)
    FGameplayAttributeData CurrentAmmo;
    ATTRIBUTE_ACCESSORS_BASIC(UAtomicHeartsAttributeSet, CurrentAmmo);

    // MaxAmmo (maximum ammo capacity)
    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxAmmo)
    FGameplayAttributeData MaxAmmo;
    ATTRIBUTE_ACCESSORS_BASIC(UAtomicHeartsAttributeSet, MaxAmmo);

    // ReloadSpeed (time to reload, lower is faster)
    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_ReloadSpeed)
    FGameplayAttributeData ReloadSpeed;
    ATTRIBUTE_ACCESSORS_BASIC(UAtomicHeartsAttributeSet, ReloadSpeed);

    // FireRate (seconds between shots)
    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_FireRate)
    FGameplayAttributeData FireRate;
    ATTRIBUTE_ACCESSORS_BASIC(UAtomicHeartsAttributeSet, FireRate);

    // Stamina (for sprint/dodge costs)
    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina)
    FGameplayAttributeData Stamina;
    ATTRIBUTE_ACCESSORS_BASIC(UAtomicHeartsAttributeSet, Stamina);

    // Energy (for ability costs)
    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Energy)
    FGameplayAttributeData Energy;
    ATTRIBUTE_ACCESSORS_BASIC(UAtomicHeartsAttributeSet, Energy);

    // MoveSpeed (replaces UClassStatsComponent manual handling)
    UPROPERTY(BlueprintReadOnly, Category = "Movement", ReplicatedUsing = OnRep_MoveSpeed)
    FGameplayAttributeData MoveSpeed;
    ATTRIBUTE_ACCESSORS_BASIC(UAtomicHeartsAttributeSet, MoveSpeed);

protected:
    // Replication Notifies
    UFUNCTION()
    virtual void OnRep_Health(const FGameplayAttributeData& OldValue);
    UFUNCTION()
    virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
    UFUNCTION()
    virtual void OnRep_Shield(const FGameplayAttributeData& OldValue);
    UFUNCTION()
    virtual void OnRep_Armor(const FGameplayAttributeData& OldValue);
    UFUNCTION()
    virtual void OnRep_DamageResistance(const FGameplayAttributeData& OldValue);
    UFUNCTION()
    virtual void OnRep_Currency(const FGameplayAttributeData& OldValue);
    UFUNCTION()
    virtual void OnRep_CurrentAmmo(const FGameplayAttributeData& OldValue);
    UFUNCTION()
    virtual void OnRep_MaxAmmo(const FGameplayAttributeData& OldValue);
    UFUNCTION()
    virtual void OnRep_ReloadSpeed(const FGameplayAttributeData& OldValue);
    UFUNCTION()
    virtual void OnRep_FireRate(const FGameplayAttributeData& OldValue);
    UFUNCTION()
    virtual void OnRep_Stamina(const FGameplayAttributeData& OldValue);
    UFUNCTION()
    virtual void OnRep_Energy(const FGameplayAttributeData& OldValue);
    UFUNCTION()
    virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldValue);
};