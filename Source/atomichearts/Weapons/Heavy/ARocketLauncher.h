// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ARocketLauncher.generated.h"

/**
 * ARocketLauncher — Solaris RL-X
 * Explosive heavy weapon. Fires homing rockets that deal area damage.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ARocketLauncher : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ARocketLauncher();

protected:
	virtual void BeginPlay() override;

public:
	// Rocket explosion radius
	UPROPERTY(EditAnywhere, Category = "Rocket")
	float ExplosionRadius = 500.f;

	// Rocket travel speed
	UPROPERTY(EditAnywhere, Category = "Rocket")
	float RocketSpeed = 2000.f;

	// Does rocket home onto targets?
	UPROPERTY(EditAnywhere, Category = "Rocket")
	bool bHomingRocket = true;
};
