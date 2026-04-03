// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ANeonRocketLauncher.generated.h"

/**
 * ANeonRocketLauncher — Neon RL-3 "Scrap"
 * Homemade rocket launcher cobbled together from scrap parts.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ANeonRocketLauncher : public ACyberWeapon
{
	GENERATED_BODY()
public:
	ANeonRocketLauncher();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, Category = "Rocket")
	float ExplosionRadius = 380.f;
	UPROPERTY(EditAnywhere, Category = "Rocket")
	float RocketSpeed = 1800.f;
	UPROPERTY(EditAnywhere, Category = "Rocket")
	bool bHomingRocket = false;
};
