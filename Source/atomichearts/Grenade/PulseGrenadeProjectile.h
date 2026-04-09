// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "Grenade/AGrenadeProjectile.h"
#include "PulseGrenadeProjectile.generated.h"

/**
 * Pulse grenade: creates a persistent zone that pulses damage over time.
 */
UCLASS()
class ATOMICHEARTS_API APulseGrenadeProjectile : public AGrenadeProjectile
{
	GENERATED_BODY()
	
public:
	APulseGrenadeProjectile();

protected:
	virtual void ApplyEffects(const FVector& ExplosionLocation) override;

	/** Damage per pulse */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pulse Grenade")
	float PulseDamage = 20.f;

	/** Zone radius */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pulse Grenade")
	float ZoneRadius = 400.f;

	/** Zone duration (seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pulse Grenade")
	float ZoneDuration = 10.f;

	/** Pulse interval (seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pulse Grenade")
	float PulseInterval = 1.f;
};