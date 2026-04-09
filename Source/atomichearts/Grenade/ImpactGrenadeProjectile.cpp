// Copyright 2024 Destiny Cyberpunk

#include "ImpactGrenadeProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

AImpactGrenadeProjectile::AImpactGrenadeProjectile()
{
	// Impact grenade explodes on hit, no fuse
	FuseTime = 0.f;
	Damage = 50.f;
	ExplosionRadius = 500.f;
}

void AImpactGrenadeProjectile::ApplyEffects(const FVector& ExplosionLocation)
{
	// Instant damage
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(this);
	
	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		Damage,
		ExplosionLocation,
		ExplosionRadius,
		nullptr,
		IgnoredActors,
		GetOwner(),
		nullptr,
		true
	);
	
#if WITH_EDITOR
	DrawDebugSphere(GetWorld(), ExplosionLocation, ExplosionRadius, 12, FColor::Red, false, 2.f);
#endif
	
	UE_LOG(LogTemp, Log, TEXT("Impact grenade exploded at %s, damage %f, radius %f"), *ExplosionLocation.ToString(), Damage, ExplosionRadius);
}