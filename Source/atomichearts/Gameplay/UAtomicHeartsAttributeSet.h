// Copyright (c) 2026 Atomic Hearts Team. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "UAtomicHeartsAttributeSet.generated.h"

/**
 * Attribute set for Atomic Hearts characters using Gameplay Ability System.
 * Contains Health, MaxHealth, Shield, Armor, DamageResistance.
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
};