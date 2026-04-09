// Copyright (c) 2024 Atomichearts. All rights reserved.

#include "Characters/ACompanionCharacter.h"
#include "Characters/AAtomichartsCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"

// =============================================================================
// ACompanionCharacter Implementation
// =============================================================================

ACompanionCharacter::ACompanionCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

    // Configure for AI companion behavior
    if (UCharacterMovementComponent* Movement = GetCharacterMovement())
    {
        Movement->bUseFlatBaseForFloorCheck = true;
        Movement->RotationRate = FRotator(0.f, 360.f, 0.f);
    }

    // Create detection sphere
    DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
    DetectionSphere->SetupAttachment(RootComponent);
    DetectionSphere->SetSphereRadius(1000.f);
    DetectionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    DetectionSphere->SetGenerateOverlapEvents(true);
    DetectionSphere->SetHiddenInGame(true); // Debug: set to false to see sphere

    // Initialize cooldowns
    BuffCooldownRemaining = 0.f;
    AttackCooldownRemaining = 0.f;
}

void ACompanionCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ACompanionCharacter, OwnerPlayer);
    DOREPLIFETIME(ACompanionCharacter, CompanionState);
    DOREPLIFETIME(ACompanionCharacter, CompanionRole);
    DOREPLIFETIME(ACompanionCharacter, CurrentTarget);
    DOREPLIFETIME(ACompanionCharacter, DefendPosition);
}

void ACompanionCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Apply role bonuses
    SetCompanionRole(CompanionRole);

    // Bind detection sphere overlap events
    if (DetectionSphere)
    {
        DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACompanionCharacter::OnDetectionSphereBeginOverlap);
        DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ACompanionCharacter::OnDetectionSphereEndOverlap);
    }

    // Start AI evaluation timer (every 0.5 seconds)
    GetWorldTimerManager().SetTimer(AIEvaluationTimerHandle, this, &ACompanionCharacter::EvaluateState, 0.5f, true);
}

void ACompanionCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!HasAuthority())
        return;

    // Update cooldowns
    BuffCooldownRemaining = FMath::Max(0.f, BuffCooldownRemaining - DeltaTime);
    AttackCooldownRemaining = FMath::Max(0.f, AttackCooldownRemaining - DeltaTime);

    switch (CompanionState)
    {
    case ECompanionState::Following:
        UpdateFollowBehavior(DeltaTime);
        break;
    case ECompanionState::Attacking:
        UpdateCombatBehavior(DeltaTime);
        break;
    case ECompanionState::Defending:
        UpdateCombatBehavior(DeltaTime);
        break;
    case ECompanionState::Supporting:
        UpdateSupportBehavior(DeltaTime);
        break;
    case ECompanionState::Waiting:
        // Do nothing, wait for commands
        break;
    default:
        break;
    }
}

void ACompanionCharacter::SetOwnerPlayer(AAtomichartsCharacter* NewOwner)
{
    if (!HasAuthority())
        return;

    OwnerPlayer = NewOwner;

    if (OwnerPlayer)
    {
        // Auto-follow when assigned
        FollowOwner();
    }
}

void ACompanionCharacter::SetCompanionRole(ECompanionRole NewRole)
{
    if (!HasAuthority())
        return;

    CompanionRole = NewRole;

    // Apply role-specific bonuses
    UCharacterMovementComponent* Movement = GetCharacterMovement();

    switch (CompanionRole)
    {
    case ECompanionRole::Vanguard:
        if (UCombatComponent* Combat = FindComponentByClass<UCombatComponent>())
        {
            Combat->TakeDamage(1.f - TankBonusArmor / 100.f); // Reduce damage taken
        }
        break;

    case ECompanionRole::Scout:
        if (Movement)
            Movement->MaxWalkSpeed += ScoutBonusSpeed;
        break;

    case ECompanionRole::Hacker:
        // Hacker bonuses handled in cyberware system
        break;

    case ECompanionRole::Sniper:
        if (UCombatComponent* Combat = FindComponentByClass<UCombatComponent>())
        {
            // Damage multiplier would be applied in combat calculations
        }
        break;

    case ECompanionRole::Support:
        // Support gets healing abilities
        break;
    }

    OnRoleChanged.Broadcast(NewRole);
}

void ACompanionCharacter::FollowOwner()
{
    if (!OwnerPlayer)
        return;

    SetCompanionState(ECompanionState::Following);
    GetWorldTimerManager().SetTimer(FollowTimerHandle, this, &ACompanionCharacter::UpdateFollowBehavior, 0.1f, true);
}

void ACompanionCharacter::StopFollowing()
{
    SetCompanionState(ECompanionState::Idle);
    GetWorldTimerManager().ClearTimer(FollowTimerHandle);
}

void ACompanionCharacter::AttackTarget(AActor* Target)
{
    if (!HasAuthority() || !Target)
        return;

    CurrentTarget = Target;
    SetCompanionState(ECompanionState::Attacking);
}

void ACompanionCharacter::DefendPosition(const FVector& Position)
{
    if (!HasAuthority())
        return;

    DefendPosition = Position;
    SetCompanionState(ECompanionState::Defending);
}

void ACompanionCharacter::UseAbility(int32 AbilityIndex)
{
    if (!HasAuthority())
        return;

    // Ability system integration - trigger specific ability
    OnAbilityUsed.Broadcast(AbilityIndex);
}

void ACompanionCharacter::SetCompanionState(ECompanionState NewState)
{
    if (!HasAuthority())
        return;

    ECompanionState OldState = CompanionState;
    CompanionState = NewState;

    OnCompanionStateChanged.Broadcast(OldState, NewState);
}

void ACompanionCharacter::OnHealthChanged(float OldValue, float NewValue)
{
    Super::OnHealthChanged(OldValue, NewValue);

    // If owner player exists and health is low, retreat or call for help
    if (OwnerPlayer && NewValue < GetMaxHealth() * 0.3f)
    {
        if (CompanionState == ECompanionState::Attacking)
        {
            // Retreat to owner
            SetCompanionState(ECompanionState::Following);
        }
    }
}

void ACompanionCharacter::UpdateFollowBehavior(float DeltaTime)
{
    if (!OwnerPlayer)
    {
        StopFollowing();
        return;
    }

    FVector OwnerLocation = OwnerPlayer->GetActorLocation();
    FVector MyLocation = GetActorLocation();
    float Distance = FVector::Dist(MyLocation, OwnerLocation);

    // Check if within follow distance
    if (Distance > AcceptableDistance)
    {
        // Move towards owner
        FVector Direction = (OwnerLocation - MyLocation).GetSafeNormal();
        
        // Add offset to stay at follow distance
        FVector TargetLocation = OwnerLocation - Direction * FollowDistance;
        TargetLocation.Z = MyLocation.Z;

        UCharacterMovementComponent* Movement = GetCharacterMovement();
        if (Movement)
        {
            Movement->MaxWalkSpeed = FollowSpeed;
            AddMovementInput(Direction, 1.f);
        }

        // Face the owner
        FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(MyLocation, OwnerLocation);
        SetActorRotation(FMath::RInterpTo(GetActorRotation(), LookAt, DeltaTime, 5.f));
    }
    else
    {
        // Close enough, just face owner
        FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(MyLocation, OwnerLocation);
        SetActorRotation(FMath::RInterpTo(GetActorRotation(), LookAt, DeltaTime, 5.f));
    }
}

void ACompanionCharacter::UpdateCombatBehavior(float DeltaTime)
{
    if (!CurrentTarget)
    {
        // No target, check if we should return to follow
        if (OwnerPlayer)
        {
            SetCompanionState(ECompanionState::Following);
        }
        return;
    }

    // Check if target is still valid
    if (!IsValid(CurrentTarget) || CurrentTarget->IsHidden())
    {
        CurrentTarget = nullptr;
        return;
    }

    FVector TargetLocation = CurrentTarget->GetActorLocation();
    FVector MyLocation = GetActorLocation();
    float Distance = FVector::Dist(MyLocation, TargetLocation);

    // Attack range check based on role
    float IdealRange = AttackRange;
    if (CompanionRole == ECompanionRole::Vanguard)
        IdealRange = 200.f;
    else if (CompanionRole == ECompanionRole::Sniper)
        IdealRange = 1500.f;

    if (Distance > IdealRange)
    {
        // Move closer
        FVector Direction = (TargetLocation - MyLocation).GetSafeNormal();
        Direction.Z = 0.f; // Keep on ground
        
        UCharacterMovementComponent* Movement = GetCharacterMovement();
        if (Movement)
        {
            Movement->MaxWalkSpeed = FollowSpeed * 1.5f; // Sprint to target
            AddMovementInput(Direction, 1.f);
        }
    }
    else
    {
        // In range, attack
        FaceRotation(UKismetMathLibrary::FindLookAtRotation(MyLocation, TargetLocation), DeltaTime);
        
        // Trigger attack animation/logic
        OnAttackTarget.Broadcast(CurrentTarget);
    }
}

void ACompanionCharacter::UpdateSupportBehavior(float DeltaTime)
{
    if (!OwnerPlayer)
        return;

    FVector OwnerLocation = OwnerPlayer->GetActorLocation();
    FVector MyLocation = GetActorLocation();
    float Distance = FVector::Dist(MyLocation, OwnerLocation);

    // Stay close to provide support
    if (Distance > FollowDistance * 1.5f)
    {
        FVector Direction = (OwnerLocation - MyLocation).GetSafeNormal();
        AddMovementInput(Direction, 1.f);
    }

    // Check for allies that need healing (Support role)
    if (CompanionRole == ECompanionRole::Support)
    {
        // Find nearby damaged allies
        TArray<AActor*> Allies;
        UGameplayStatics::GetOverlappingActors(this, Allies, ACompanionCharacter::StaticClass());
        
        for (AActor* Ally : Allies)
        {
            if (ACompanionCharacter* Companion = Cast<ACompanionCharacter>(Ally))
            {
                if (Companion->GetHealth() < Companion->GetMaxHealth() * 0.5f)
                {
                    // Use healing ability
                    UseAbility(0);
                    break;
                }
            }
        }
    }
}

void ACompanionCharacter::OnDetectionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!HasAuthority())
        return;

    // Only consider actors with tag "Enemy"
    if (OtherActor && OtherActor->ActorHasTag(TEXT("Enemy")))
    {
        // Avoid duplicates
        if (!DetectedEnemies.Contains(OtherActor))
        {
            DetectedEnemies.Add(OtherActor);
            UE_LOG(LogTemp, Log, TEXT("Companion detected enemy: %s"), *OtherActor->GetName());
        }
    }
}

void ACompanionCharacter::OnDetectionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!HasAuthority())
        return;

    if (OtherActor && DetectedEnemies.Contains(OtherActor))
    {
        DetectedEnemies.Remove(OtherActor);
        UE_LOG(LogTemp, Log, TEXT("Companion lost enemy: %s"), *OtherActor->GetName());
    }
}

void ACompanionCharacter::EvaluateState()
{
    if (!HasAuthority())
        return;

    // If owner health low (<50%) and role is Support, cast buff
    if (OwnerPlayer && CompanionRole == ECompanionRole::Support)
    {
        float HealthPercent = OwnerPlayer->GetHealth() / OwnerPlayer->GetMaxHealth();
        if (HealthPercent < 0.5f)
        {
            CastBuff();
            return;
        }
    }

    // If enemies detected, attack nearest
    if (DetectedEnemies.Num() > 0)
    {
        PerformAttack();
        return;
    }

    // Otherwise follow owner (if exists)
    if (OwnerPlayer)
    {
        FollowOwner();
    }
}

void ACompanionCharacter::CastBuff()
{
    if (!HasAuthority())
        return;

    if (BuffCooldownRemaining > 0.f)
        return;

    // Apply healing or buff to owner
    if (OwnerPlayer)
    {
        // Assuming owner has a method ApplyHealing(float Amount)
        // OwnerPlayer->ApplyHealing(SupportBonusHealing);
        // For now, just log
        UE_LOG(LogTemp, Log, TEXT("Companion cast buff on owner"));
    }

    BuffCooldownRemaining = 10.f; // Cooldown 10 seconds
}

void ACompanionCharacter::PerformAttack()
{
    if (!HasAuthority())
        return;

    if (AttackCooldownRemaining > 0.f)
        return;

    // Find nearest enemy
    AActor* NearestEnemy = nullptr;
    float NearestDist = FLT_MAX;
    FVector MyLocation = GetActorLocation();
    for (AActor* Enemy : DetectedEnemies)
    {
        if (!IsValid(Enemy))
            continue;
        float Dist = FVector::Dist(MyLocation, Enemy->GetActorLocation());
        if (Dist < NearestDist)
        {
            NearestDist = Dist;
            NearestEnemy = Enemy;
        }
    }
    if (!NearestEnemy)
        return;

    // Attack based on role
    switch (CompanionRole)
    {
    case ECompanionRole::Vanguard:
        // Melee attack
        AttackTarget(NearestEnemy);
        break;
    case ECompanionRole::Sniper:
        // Spawn projectile (call ability)
        UseAbility(1);
        break;
    case ECompanionRole::Hacker:
        // Apply debuff (call ability)
        UseAbility(2);
        break;
    case ECompanionRole::Support:
        // Support role may also attack with weak ability
        UseAbility(0);
        break;
    case ECompanionRole::Scout:
        // Scout may attack with ranged
        UseAbility(3);
        break;
    default:
        break;
    }

    AttackCooldownRemaining = 2.f; // Cooldown 2 seconds
    UE_LOG(LogTemp, Log, TEXT("Companion attacked enemy: %s"), *NearestEnemy->GetName());
}

