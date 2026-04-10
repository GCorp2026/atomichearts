// Copyright 2026 Atomic Hearts Team

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatDamageable.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "HealthRegenComponent.generated.h"

/**
 * Component that provides health regeneration over time.
 * Can be attached to any actor implementing ICombatDamageable.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ATOMICHEARTS_API UHealthRegenComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHealthRegenComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
    // Enable/disable regeneration
    UFUNCTION(BlueprintCallable, Category = "Health Regen")
    void SetRegenEnabled(bool bEnabled);

    // Set regeneration rate (health per second)
    UFUNCTION(BlueprintCallable, Category = "Health Regen")
    void SetRegenRate(float HealthPerSecond);

    // Set delay after taking damage before regeneration resumes
    UFUNCTION(BlueprintCallable, Category = "Health Regen")
    void SetDamageCooldown(float CooldownSeconds);

    // Get current health regen rate
    UFUNCTION(BlueprintPure, Category = "Health Regen")
    float GetRegenRate() const { return RegenRate; }

    // Is regeneration currently active?
    UFUNCTION(BlueprintPure, Category = "Health Regen")
    bool IsRegenActive() const { return bIsActive; }

private:
    void ApplyRegen(float DeltaTime);
    void OnDamageTaken(float Damage, AActor* DamageCauser);
    UAbilitySystemComponent* GetOwnerASC() const;
    void ApplyGASHealing(float RegenAmount);

private:
    // Rate of health regeneration (health per second)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Regen", meta = (AllowPrivateAccess = "true"))
    float RegenRate = 5.0f;

    // Delay after taking damage before regeneration resumes (seconds)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Regen", meta = (AllowPrivateAccess = "true"))
    float DamageCooldown = 3.0f;

    // Current cooldown timer
    float CooldownTimer = 0.0f;

    // Is regeneration enabled?
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Regen", meta = (AllowPrivateAccess = "true"))
    bool bIsActive = true;

    // Reference to the damageable interface
    TScriptInterface<ICombatDamageable> DamageableInterface;
};