// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AGhostRocketLauncher.generated.h"

/**
 * AGhostRocketLauncher — Ghost RL-5 "Phantom"
 * Stealth explosive launcher. Minimized visual and audio signature.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AGhostRocketLauncher : public ACyberWeapon
{
	GENERATED_BODY()
public:
	AGhostRocketLauncher();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, Category = "Rocket")
	float ExplosionRadius = 420.f;
	UPROPERTY(EditAnywhere, Category = "Rocket")
	float RocketSpeed = 2000.f;
	UPROPERTY(EditAnywhere, Category = "Rocket")
	bool bHomingRocket = true;
};
