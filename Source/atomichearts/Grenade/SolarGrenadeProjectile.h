// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "Grenade/AGrenadeProjectile.h"
#include "SolarGrenadeProjectile.generated.h"

/**
 * Solar grenade: creates a burn zone that applies damage over time.
 */
UCLASS()
class ATOMICHEARTS_API ASolarGrenadeProjectile : public AGrenadeProjectile
{
	GENERATED_BODY()
	
public:
	ASolarGrenadeProjectile();

protected:
	virtual void ApplyEffects(const FVector& ExplosionLocation) override;

	/** Burn damage per tick */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solar Grenade")
	float BurnDamage = 10.f;

	/** Zone radius */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solar Grenade")
	float ZoneRadius = 400.f;

	/** Zone duration (seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solar Grenade")
	float ZoneDuration = 5.f;

	/** Burn interval (seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solar Grenade")
	float BurnInterval = 0.5f;
};