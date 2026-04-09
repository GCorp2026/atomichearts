// Copyright 2024 Destiny Cyberpunk

#include "PulseGrenadeProjectile.h"
#include "Grenade/PulseZoneActor.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

APulseGrenadeProjectile::APulseGrenadeProjectile()
{
	// Pulse grenade has a short fuse
	FuseTime = 1.f;
	Damage = 0.f; // No initial damage
	ExplosionRadius = 0.f;
}

void APulseGrenadeProjectile::ApplyEffects(const FVector& ExplosionLocation)
{
	// Spawn pulse zone
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		APulseZoneActor* Zone = World->SpawnActor<APulseZoneActor>(APulseZoneActor::StaticClass(), ExplosionLocation, FRotator::ZeroRotator, SpawnParams);
		if (Zone)
		{
			Zone->SetPulseDamage(PulseDamage);
			Zone->SetZoneRadius(ZoneRadius);
			Zone->SetPulseInterval(PulseInterval);
			Zone->SetZoneDuration(ZoneDuration);
			UE_LOG(LogTemp, Log, TEXT("Pulse zone created at %s"), *ExplosionLocation.ToString());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to spawn pulse zone"));
		}
	}

#if WITH_EDITOR
	DrawDebugSphere(World, ExplosionLocation, ZoneRadius, 12, FColor::Blue, false, ZoneDuration);
#endif
}