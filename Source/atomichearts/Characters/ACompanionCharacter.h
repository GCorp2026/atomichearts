// Copyright (c) 2024 Atomichearts. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ANPCCharacter.h"
#include "Components/TimelineComponent.h"
#include "CompanionCharacter.generated.h"

class AAtomicheartsCharacter;
class USphereComponent;

/**
 * ECompanionState - AI behavior state for companions
 */
UENUM(BlueprintType)
enum class ECompanionState : uint8
{
    Idle UMETA(DisplayName = "Idle"),
    Following UMETA(DisplayName = "Following"),
    Attacking UMETA(DisplayName = "Attacking"),
    Defending UMETA(DisplayName = "Defending"),
    Supporting UMETA(DisplayName = "Supporting"),
    Waiting UMETA(DisplayName = "Waiting")
};

/**
 * ECompanionRole - Companion specialization role
 */
UENUM(BlueprintType)
enum class ECompanionRole : uint8
{
    Vanguard UMETA(DisplayName = "Vanguard (Tank)"),
    Support UMETA(DisplayName = "Support (Healer)"),
    Scout UMETA(DisplayName = "Scout (Recon)"),
    Hacker UMETA(DisplayName = "Hacker (Tech)"),
    Sniper UMETA(DisplayName = "Sniper (Ranged)")
};

/**
 * ACompanionCharacter - AI-controlled ally that follows and assists player
 */
UCLASS()
class ATOMICHEARTS_API ACompanionCharacter : public ANPCCharacter
{
    GENERATED_BODY()

public:
    ACompanionCharacter();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void Tick(float DeltaTime) override;
    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    // Companion Management
    UFUNCTION(BlueprintCallable)
    void SetOwnerPlayer(AAtomichartsCharacter* NewOwner);

    UFUNCTION(BlueprintPure)
    AAtomichartsCharacter* GetOwnerPlayer() const { return OwnerPlayer; }

    UFUNCTION(BlueprintCallable)
    void SetCompanionRole(ECompanionRole NewRole);

    UFUNCTION(BlueprintPure)
    ECompanionRole GetCompanionRole() const { return CompanionRole; }

    // Behavior Control
    UFUNCTION(BlueprintCallable)
    void FollowOwner();

    UFUNCTION(BlueprintCallable)
    void StopFollowing();

    UFUNCTION(BlueprintCallable)
    void AttackTarget(AActor* Target);

    UFUNCTION(BlueprintCallable)
    void DefendPosition(const FVector& Position);

    UFUNCTION(BlueprintCallable)
    void UseAbility(int32 AbilityIndex);

    // State
    UFUNCTION(BlueprintPure)
    ECompanionState GetCompanionState() const { return CompanionState; }

    UFUNCTION(BlueprintCallable)
    void SetCompanionState(ECompanionState NewState);

protected:
    virtual void BeginPlay() override;
    virtual void OnHealthChanged(float OldValue, float NewValue) override;

private:
    void UpdateFollowBehavior(float DeltaTime);
    void UpdateCombatBehavior(float DeltaTime);
    void UpdateSupportBehavior(float DeltaTime);

    // Owner Reference
    UPROPERTY(Replicated)
    AAtomichartsCharacter* OwnerPlayer = nullptr;

    // Companion State
    UPROPERTY(Replicated)
    ECompanionState CompanionState = ECompanionState::Idle;

    UPROPERTY(Replicated)
    ECompanionRole CompanionRole = ECompanionRole::Vanguard;

    // Follow Settings
    UPROPERTY(EditAnywhere)
    float FollowDistance = 300.f;

    UPROPERTY(EditAnywhere)
    float AcceptableDistance = 150.f;

    UPROPERTY(EditAnywhere)
    float FollowSpeed = 400.f;

    // Combat Settings
    UPROPERTY(EditAnywhere)
    float EngagementRange = 1000.f;

    UPROPERTY(EditAnywhere)
    float AttackRange = 500.f;

    UPROPERTY(EditAnywhere)
    float DefendRadius = 200.f;

    // Target
    UPROPERTY(Replicated)
    AActor* CurrentTarget = nullptr;

    UPROPERTY(Replicated)
    FVector DefendPosition;

    // Role Bonuses
    UPROPERTY(EditAnywhere)
    float TankBonusArmor = 50.f;

    UPROPERTY(EditAnywhere)
    float VanguardDamageReduction = 0.5f; // 50% damage reduction when role is Vanguard

    UPROPERTY(EditAnywhere)
    float SupportBonusHealing = 20.f;

    UPROPERTY(EditAnywhere)
    float ScoutBonusSpeed = 100.f;

    UPROPERTY(EditAnywhere)
    float HackerBonusHack = 30.f;

    UPROPERTY(EditAnywhere)
    float SniperBonusDamage = 25.f;

    // Timers
    FTimerHandle FollowTimerHandle;
    FTimerHandle CombatTimerHandle;
    FTimerHandle AIEvaluationTimerHandle;

    // AI Detection
    UPROPERTY(VisibleAnywhere)
    USphereComponent* DetectionSphere;

    UPROPERTY()
    TArray<AActor*> DetectedEnemies;

    // Cooldowns
    float BuffCooldownRemaining;
    float AttackCooldownRemaining;

    // AI Evaluation
    void EvaluateState();
    void CastBuff();
    void PerformAttack();
    void OnDetectionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    void OnDetectionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
