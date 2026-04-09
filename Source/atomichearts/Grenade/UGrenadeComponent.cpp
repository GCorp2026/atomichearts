// Copyright 2024 Destiny Cyberpunk

#include "UGrenadeComponent.h"
#include "Grenade/AGrenadeProjectile.h"
#include "Grenade/ImpactGrenadeProjectile.h"
#include "Grenade/PulseGrenadeProjectile.h"
#include "Grenade/SolarGrenadeProjectile.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"

UGrenadeComponent::UGrenadeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrenadeComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGrenadeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CooldownRemaining > 0.f)
	{
		CooldownRemaining -= DeltaTime;
		if (CooldownRemaining < 0.f)
			CooldownRemaining = 0.f;
	}
}

void UGrenadeComponent::SetGrenadeType(EAbilityType NewType)
{
	GrenadeType = NewType;
}

void UGrenadeComponent::SetCooldown(float NewCooldown)
{
	Cooldown = NewCooldown;
}

void UGrenadeComponent::ThrowGrenade()
{
	if (!HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("ThrowGrenade called on client - ignoring"));
		return;
	}

	if (!IsReady())
	{
		UE_LOG(LogTemp, Warning, TEXT("Grenade on cooldown"));
		return;
	}
	
	AActor* Owner = GetOwner();
	if (!Owner)
		return;

	FVector Location = Owner->GetActorLocation() + Owner->GetActorForwardVector() * 100.f;
	FRotator Rotation = Owner->GetActorRotation();
	
	AGrenadeProjectile* Projectile = SpawnProjectile(Location, Rotation);
	if (Projectile)
	{
		Projectile->SetDamage(Damage);
		Projectile->SetExplosionRadius(Radius);
		
		UProjectileMovementComponent* Movement = Projectile->GetProjectileMovement();
		if (Movement)
		{
			Movement->Velocity = Owner->GetActorForwardVector() * ThrowStrength;
		}
		
		CooldownRemaining = Cooldown;
		UE_LOG(LogTemp, Log, TEXT("Grenade thrown (Type: %d)"), (uint8)GrenadeType);
	}
}

AGrenadeProjectile* UGrenadeComponent::SpawnProjectile(const FVector& Location, const FRotator& Rotation)
{
	UWorld* World = GetWorld();
	if (!World)
		return nullptr;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = Cast<APawn>(GetOwner());
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	TSubclassOf<AGrenadeProjectile> ProjectileClass = AGrenadeProjectile::StaticClass();
	
	switch (GrenadeType)
	{
	case EAbilityType::ImpactGrenade:
		ProjectileClass = AImpactGrenadeProjectile::StaticClass();
		break;
	case EAbilityType::PulseGrenade:
		ProjectileClass = APulseGrenadeProjectile::StaticClass();
		break;
	case EAbilityType::SolarGrenade:
		ProjectileClass = ASolarGrenadeProjectile::StaticClass();
		break;
	default:
		// Fallback to base class, but log warning
		UE_LOG(LogTemp, Warning, TEXT("Unknown grenade type %d, using base projectile"), (uint8)GrenadeType);
		break;
	}
	
	AGrenadeProjectile* Projectile = World->SpawnActor<AGrenadeProjectile>(ProjectileClass, Location, Rotation, SpawnParams);
	return Projectile;
}

void UGrenadeComponent::OnExplode(const FVector& ExplosionLocation)
{
	ApplyEffects(ExplosionLocation);
}

void UGrenadeComponent::ApplyEffects(const FVector& ExplosionLocation)
{
	// Default: instant damage in radius
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(GetOwner());
	
	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		Damage,
		ExplosionLocation,
		Radius,
		nullptr, // DamageTypeClass
		IgnoredActors,
		GetOwner(),
		nullptr, // Controller
		true // bDoFullDamage
	);
	
	// Debug visualization
#if WITH_EDITOR
	DrawDebugSphere(GetWorld(), ExplosionLocation, Radius, 12, FColor::Red, false, 2.f);
#endif
	
	UE_LOG(LogTemp, Log, TEXT("Grenade exploded at %s, damage %f, radius %f"), *ExplosionLocation.ToString(), Damage, Radius);
}