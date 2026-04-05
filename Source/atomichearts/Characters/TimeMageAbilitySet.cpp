// Copyright 2024 Destiny Cyberpunk

#include "TimeMageAbilitySet.h"
#include "EClassType.h"
#include "AAtomichartsCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"

// =============================================================================
// UTimeFreezeEffect Implementation
// =============================================================================

UTimeFreezeEffect::UTimeFreezeEffect()
{
	// Infinite duration while active, removed by ability
	FGameplayEffectSpec Spec;
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FScalableFloat(4.f); // Default 4 seconds
}

// =============================================================================
// UTimeSlowEffect Implementation
// =============================================================================

UTimeSlowEffect::UTimeSlowEffect()
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FScalableFloat(6.f);
}

// =============================================================================
// UPhaseShiftEffect Implementation
// =============================================================================

UPhaseShiftEffect::UPhaseShiftEffect()
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FScalableFloat(3.f);
}

// =============================================================================
// AChronoTrap Implementation
// =============================================================================

AChronoTrap::AChronoTrap()
{
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
}

void AChronoTrap::Initialize(float Duration, float Radius, float SlowPercent, AActor* Owner)
{
	TrapDuration = Duration;
	EffectRadius = Radius;
	SlowPercent = SlowPercent;
	TrapOwner = Owner;
}

void AChronoTrap::BeginPlay()
{
	Super::BeginPlay();

	// Set lifetime
	GetWorldTimerManager().SetTimer(LifetimeHandle, this, &AChronoTrap::OnTrapTriggered, TrapDuration, false);
}

void AChronoTrap::OnTrapTriggered()
{
	// When trap expires or triggered, apply slow to enemies in radius
	if (TrapOwner && GetWorld())
	{
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(TrapOwner);

		TArray<AActor*> OutActors;
		
		UGameplayStatics::SphereOverlapActors(
			GetWorld(),
			GetActorLocation(),
			EffectRadius,
			ObjectTypes,
			nullptr,
			ActorsToIgnore,
			OutActors
		);

		for (AActor* Actor : OutActors)
		{
			if (Actor && !Actor->IsA<APawn>()->IsPlayerControlled())
			{
				// Apply slow effect to enemies
				// In full GAS: ApplyGameplayEffect(Actor, SlowEffect)
				
				// Fallback: Modify movement directly
				if (UCharacterMovementComponent* Movement = Actor->FindComponentByClass<UCharacterMovementComponent>())
				{
					Movement->MaxWalkSpeed *= (1.f - SlowPercent);
				}
			}
		}
	}

	// Destroy trap after effect
	Destroy();
}

// =============================================================================
// UTimeMageAbilitySet Implementation
// =============================================================================

UTimeMageAbilitySet::UTimeMageAbilitySet()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTimeMageAbilitySet::BeginPlay()
{
	Super::BeginPlay();
}

void UTimeMageAbilitySet::ExecuteTimeStop(float Radius, float Duration)
{
	AActor* Owner = GetOwner();
	if (!Owner)
		return;

	// Server-only execution
	if (!Owner->HasAuthority())
		return;

	// Find all enemies in radius and freeze them
	TArray<AActor*> Enemies = GetEnemiesInRadius(Owner, Radius);
	
	for (AActor* Enemy : Enemies)
	{
		if (!Enemy)
			continue;

		// Freeze enemy by disabling movement and collision
		if (UCharacterMovementComponent* Movement = Enemy->FindComponentByClass<UCharacterMovementComponent>())
		{
			Movement->DisableMovement();
			
			// Re-enable after duration
			FTimerHandle TimerHandle;
			Owner->GetWorldTimerManager().SetTimer(TimerHandle, [Movement]()
			{
				Movement->SetMovementMode(MOVE_Walking);
			}, Duration, false);
		}

		// Also disable capsule collision briefly
		if (UCapsuleComponent* Capsule = Enemy->FindComponentByClass<UCapsuleComponent>())
		{
			Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			
			FTimerHandle TimerHandle;
			Owner->GetWorldTimerManager().SetTimer(TimerHandle, [Capsule]()
			{
				Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			}, Duration, false);
		}

		// Visual feedback - blue time freeze effect
		// OnAbilityEffect.Broadcast(EAbilityType::TimeStop, true);
	}
}

void UTimeMageAbilitySet::ExecuteTimeSlow(float Radius, float SlowPercent, float Duration)
{
	AActor* Owner = GetOwner();
	if (!Owner)
		return;

	if (!Owner->HasAuthority())
		return;

	TArray<AActor*> Enemies = GetEnemiesInRadius(Owner, Radius);

	for (AActor* Enemy : Enemies)
	{
		if (!Enemy)
			continue;

		if (UCharacterMovementComponent* Movement = Enemy->FindComponentByClass<UCharacterMovementComponent>())
		{
			float OriginalSpeed = Movement->MaxWalkSpeed;
			Movement->MaxWalkSpeed *= (1.f - SlowPercent); // e.g., 50% slow

			// Restore after duration
			FTimerHandle TimerHandle;
			Owner->GetWorldTimerManager().SetTimer(TimerHandle, [Movement, OriginalSpeed]()
			{
				if (Movement)
				{
					Movement->MaxWalkSpeed = OriginalSpeed;
				}
			}, Duration, false);
		}
	}
}

AChronoTrap* UTimeMageAbilitySet::PlaceChronoTrap(float Radius, float SlowPercent, float Duration)
{
	AActor* Owner = GetOwner();
	if (!Owner)
		return nullptr;

	if (!Owner->HasAuthority())
		return nullptr;

	// Spawn trap at owner location
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Owner;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossible;

	FVector SpawnLocation = Owner->GetActorLocation();
	SpawnLocation.Z -= Owner->GetSimpleCollisionHalfHeight(); // Place on ground

	AChronoTrap* Trap = Owner->GetWorld()->SpawnActor<AChronoTrap>(
		AChronoTrap::StaticClass(),
		SpawnLocation,
		FRotator::ZeroRotator,
		SpawnParams
	);

	if (Trap)
	{
		Trap->Initialize(Duration, Radius, SlowPercent, Owner);
	}

	return Trap;
}

void UTimeMageAbilitySet::ExecutePhaseShift(float Duration)
{
	AActor* Owner = GetOwner();
	if (!Owner)
		return;

	if (!Owner->HasAuthority())
		return;

	// Make owner intangible - pass through enemies
	bIsPhaseShifted = true;
	PhaseShiftEndTime = Owner->GetWorld()->GetTimeSeconds() + Duration;

	if (UCapsuleComponent* Capsule = Owner->FindComponentByClass<UCapsuleComponent>())
	{
		// Disable collision with enemies
		Capsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	}

	// Make transparent
	if (AAtomichartsCharacter* Char = Cast<AAtomichartsCharacter>(Owner))
	{
		// Reduce opacity for visual feedback
		if (USkeletalMeshComponent* Mesh = Char->GetMesh())
		{
			Mesh->SetScalarParameterValueOnMaterials(FName("Opacity"), 0.5f);
		}
	}

	// End phase shift after duration
	Owner->GetWorldTimerManager().SetTimer(FPhaseShiftTimer, [this, Owner]()
	{
		bIsPhaseShifted = false;
		
		if (UCapsuleComponent* Capsule = Owner->FindComponentByClass<UCapsuleComponent>())
		{
			Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		}

		if (AAtomichartsCharacter* Char = Cast<AAtomichartsCharacter>(Owner))
		{
			if (USkeletalMeshComponent* Mesh = Char->GetMesh())
			{
				Mesh->SetScalarParameterValueOnMaterials(FName("Opacity"), 1.f);
			}
		}
	}, Duration, false);
}

TArray<AActor*> UTimeMageAbilitySet::GetEnemiesInRadius(AActor* Owner, float Radius)
{
	TArray<AActor*> Enemies;

	if (!Owner || !Owner->GetWorld())
		return Enemies;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Owner);

	TArray<AActor*> OutActors;
	UGameplayStatics::SphereOverlapActors(
		Owner->GetWorld(),
		Owner->GetActorLocation(),
		Radius,
		ObjectTypes,
		nullptr,
		ActorsToIgnore,
		OutActors
	);

	// Filter for enemies (non-team members, non-owner)
	for (AActor* Actor : OutActors)
	{
		if (Actor && Actor != Owner)
		{
			// Check if it's an enemy NPC or player we can affect
			// In full implementation, would check team/faction
			if (Actor->IsA<APawn>())
			{
				Enemies.Add(Actor);
			}
		}
	}

	return Enemies;
}
