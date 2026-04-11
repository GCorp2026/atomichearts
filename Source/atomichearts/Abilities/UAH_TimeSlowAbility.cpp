// Copyright 2024 Atomichearts. All rights reserved.
#include "UAH_TimeSlowAbility.h"
#include "Characters/TimeMageAbilitySet.h"
#include "AbilitySystemComponent.h"

UAH_TimeSlowAbility::UAH_TimeSlowAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    TimeSlowEffectClass = UTimeSlowEffect::StaticClass();
}

void UAH_TimeSlowAbility::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    if (!HasAuthority(&ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    if (!ActorInfo || !ActorInfo->AbilitySystemComponent.IsValid())
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    // Commit ability cost FIRST (before applying effect)
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    // Apply Time Slow effect to the caster (self)
    if (TimeSlowEffectClass)
    {
        FGameplayEffectContextHandle ContextHandle = ActorInfo->AbilitySystemComponent->MakeEffectContext();
        ContextHandle.AddSourceObject(this);
        FGameplayEffectSpecHandle SpecHandle = ActorInfo->AbilitySystemComponent->MakeOutgoingSpec(
            TimeSlowEffectClass,
            GetAbilityLevel(),
            ContextHandle
        );
        if (SpecHandle.IsValid())
        {
            ActorInfo->AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
        }
    }

    // Success
    EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}