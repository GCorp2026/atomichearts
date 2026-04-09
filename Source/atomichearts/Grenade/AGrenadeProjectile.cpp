// Copyright 2024 Destiny Cyberpunk

#include "AGrenadeProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"

AGrenadeProjectile::AGrenadeProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	bReplicateMovement = true;

	// Create collision sphere
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->InitSphereRadius(10.f);
	CollisionSphere->SetCollisionProfileName(TEXT("Projectile"));
	CollisionSphere->OnComponentHit.AddDynamic(this, &AGrenadeProjectile::OnHit);

	// Create movement component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = CollisionSphere;
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->MaxSpeed = 1500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.3f;
	ProjectileMovement->SetIsReplicated(true);

	// Create particle system (placeholder)
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystem->SetupAttachment(RootComponent);
	ParticleSystem->bAutoActivate = true;
}

void AGrenadeProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGrenadeProjectile, Damage);
	DOREPLIFETIME(AGrenadeProjectile, ExplosionRadius);
}

void AGrenadeProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Set fuse timer
	if (FuseTime > 0.f)
	{
		FTimerHandle FuseTimerHandle;
		GetWorldTimerManager().SetTimer(FuseTimerHandle, this, &AGrenadeProjectile::OnFuseExpired, FuseTime, false);
	}
}

void AGrenadeProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Explode on hit
	Explode();
}

void AGrenadeProjectile::OnFuseExpired()
{
	// Explode after fuse time
	Explode();
}

void AGrenadeProjectile::Explode()
{
	// Prevent multiple explosions
	if (!GetWorld())
		return;

	ApplyEffects(GetActorLocation());

	// Destroy projectile
	Destroy();
}

void AGrenadeProjectile::ApplyEffects(const FVector& ExplosionLocation)
{
	// Default: instant damage in radius
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(this);
	
	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		Damage,
		ExplosionLocation,
		ExplosionRadius,
		nullptr, // DamageTypeClass
		IgnoredActors,
		GetOwner(),
		nullptr, // Controller
		true // bDoFullDamage
	);
	
	// Debug visualization
#if WITH_EDITOR
	DrawDebugSphere(GetWorld(), ExplosionLocation, ExplosionRadius, 12, FColor::Red, false, 2.f);
#endif
	
	UE_LOG(LogTemp, Log, TEXT("Grenade exploded at %s, damage %f, radius %f"), *ExplosionLocation.ToString(), Damage, ExplosionRadius);
}