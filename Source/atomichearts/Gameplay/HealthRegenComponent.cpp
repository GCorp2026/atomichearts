// Copyright 2026 Atomic Hearts Team

#include "HealthRegenComponent.h"
#include "Game/AAtomichartsGameState.h"
#include "Interfaces/CombatDamageable.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffects/HealingEffect.h"

UHealthRegenComponent::UHealthRegenComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UHealthRegenComponent::BeginPlay()
{
    Super::BeginPlay();

    // Cache the damageable interface from the owner
    AActor* Owner = GetOwner();
    if (Owner)
    {
        DamageableInterface = TScriptInterface<ICombatDamageable>(Owner);
        if (DamageableInterface)
        {
            DamageableInterface->AddDamageTakenHandler(OnDamageTaken);
        }
    }
}

void UHealthRegenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!bIsActive)
    {
        return;
    }

    if (CooldownTimer > 0.0f)
    {
        CooldownTimer -= DeltaTime;
    }
    else
    {
        ApplyRegen(DeltaTime);
    }
}

void UHealthRegenComponent::SetRegenEnabled(bool bEnabled)
{
    bIsActive = bEnabled;
    if (!bEnabled)
    {
        CooldownTimer = 0.0f;
    }
}

void UHealthRegenComponent::SetRegenRate(float HealthPerSecond)
{
    RegenRate = FMath::Max(0.0f, HealthPerSecond);
}

void UHealthRegenComponent::SetDamageCooldown(float CooldownSeconds)
{
    DamageCooldown = FMath::Max(0.0f, CooldownSeconds);
}

void UHealthRegenComponent::OnDamageTaken(float Damage, AActor* DamageCauser)
{
    CooldownTimer = DamageCooldown;
}

void UHealthRegenComponent::ApplyRegen(float DeltaTime)
{
    if (!DamageableInterface)
    {
        return;
    }

    float CurrentHealth = DamageableInterface->GetHealth();
    float MaxHealth = DamageableInterface->GetMaxHealth();

    if (CurrentHealth >= MaxHealth)
    {
        return;
    }

    float RegenAmount = RegenRate * DeltaTime;
    
    // Try GAS healing path if available
    UAbilitySystemComponent* ASC = GetOwnerASC();
    if (ASC)
    {
        ApplyGASHealing(RegenAmount);
    }
    else
    {
        // Fallback to direct healing
        float NewHealth = FMath::Clamp(CurrentHealth + RegenAmount, 0.0f, MaxHealth);
        DamageableInterface->SetHealth(NewHealth);
    }
}

UAbilitySystemComponent* UHealthRegenComponent::GetOwnerASC() const
{
    AActor* Owner = GetOwner();
    if (!Owner) return nullptr;
    IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Owner);
    if (!ASI) return nullptr;
    return ASI->GetAbilitySystemComponent();
}

void UHealthRegenComponent::ApplyGASHealing(float RegenAmount)
{
    UAbilitySystemComponent* ASC = GetOwnerASC();
    if (!ASC)
    {
        return;
    }

    // Create a spec from the healing effect class
    TSubclassOf<UGameplayEffect> HealingEffectClass = UHealingEffect::StaticClass();
    if (!HealingEffectClass)
    {
        return;
    }

    FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(HealingEffectClass, 1.0f, ASC->MakeEffectContext());
    if (SpecHandle.IsValid())
    {
        // Set the SetByCaller magnitude using DataName "Healing"
        SpecHandle.Data->SetSetByCallerMagnitude(FName("Healing"), RegenAmount);
        // Apply the effect to self
        ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
    }
}
