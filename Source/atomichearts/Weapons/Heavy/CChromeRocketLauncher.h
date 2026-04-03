// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "CChromeRocketLauncher.generated.h"

/**
 * CChromeRocketLauncher — Chrome RL-7 "Crusader"
 * Holy rocket launcher. Rockets deal bonus damage to corrupted targets.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API CChromeRocketLauncher : public ACyberWeapon
{
	GENERATED_BODY()
public:
	CChromeRocketLauncher();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, Category = "Rocket")
	float ExplosionRadius = 480.f;
	UPROPERTY(EditAnywhere, Category = "Rocket")
	float RocketSpeed = 2400.f;
	UPROPERTY(EditAnywhere, Category = "Rocket")
	bool bHomingRocket = true;
};
