// Copyright 2024 Destiny Cyberpunk

#include "SolarGrenadeProjectile.h"
#include "Grenade/SolarBurnZoneActor.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ASolarGrenadeProjectile::ASolarGrenadeProjectile()
{
	// Solar grenade has a short fuse
	FuseTime = 1.f;
	Damage = 30.f; // Moderate initial damage
	ExplosionRadius = 400.f;
}

void ASolarGrenadeProjectile::ApplyEffects(const FVector& ExplosionLocation)
{
	// First, apply base damage (radial)
	Super::ApplyEffects(ExplosionLocation);

	// Spawn burn zone
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ASolarBurnZoneActor* Zone = World->SpawnActor<ASolarBurnZoneActor>(ASolarBurnZoneActor::StaticClass(), ExplosionLocation, FRotator::ZeroRotator, SpawnParams);
		if (Zone)
		{
			Zone->SetBurnDamage(BurnDamage);
			Zone->SetZoneRadius(ZoneRadius);
			Zone->SetBurnDuration(ZoneDuration);
			Zone->SetBurnInterval(BurnInterval);
			UE_LOG(LogTemp, Log, TEXT("Solar grenade spawned burn zone at %s"), *ExplosionLocation.ToString());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to spawn solar burn zone"));
		}
	}

#if WITH_EDITOR
	DrawDebugSphere(World, ExplosionLocation, ZoneRadius, 12, FColor::Orange, false, ZoneDuration);
#endif
}