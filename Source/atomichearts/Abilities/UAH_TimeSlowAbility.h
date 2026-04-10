// Copyright 2024 Atomichearts. All rights reserved.
#pragma once
#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "UAH_TimeSlowAbility.generated.h"

/**
 * Gameplay Ability for Time Slow effect.
 * Applies UTimeSlowEffect to the target (usually the caster).
 */
UCLASS()
class ATOMICHEARTS_API UAH_TimeSlowAbility : public UGameplayAbility
{
    GENERATED_BODY()
public:
    UAH_TimeSlowAbility();

    virtual void ActivateAbility(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;

protected:
    /** The Gameplay Effect class to apply for Time Slow */
    UPROPERTY(EditDefaultsOnly, Category = "Time Slow")
    TSubclassOf<class UGameplayEffect> TimeSlowEffectClass;
};