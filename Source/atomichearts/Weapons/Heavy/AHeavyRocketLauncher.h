// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ARocketLauncher.generated.h"

/**
 * AHeavyRocketLauncher — Axiom RL-9 "Hellfire"
 * Incendiary rockets that deal burn damage over time.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AHeavyRocketLauncher : public ACyberWeapon
{
	GENERATED_BODY()
public:
	AHeavyRocketLauncher();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, Category = "Rocket")
	float ExplosionRadius = 450.f;
	UPROPERTY(EditAnywhere, Category = "Rocket")
	float BurnDamage = 30.f;
	UPROPERTY(EditAnywhere, Category = "Rocket")
	float BurnDuration = 3.f;
	UPROPERTY(EditAnywhere, Category = "Rocket")
	float RocketSpeed = 2200.f;
};
