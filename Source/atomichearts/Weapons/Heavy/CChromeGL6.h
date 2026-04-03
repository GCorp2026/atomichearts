// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "CChromeGL6.generated.h"

/**
 * CChromeGL6 — Chrome GL-6 "Breacher"
 * Door-opening breaching grenade launcher.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API CChromeGL6 : public ACyberWeapon
{
	GENERATED_BODY()
public:
	CChromeGL6();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, Category = "Grenade")
	float ExplosionRadius = 300.f;
	UPROPERTY(EditAnywhere, Category = "Grenade")
	float ProjectileSpeed = 1200.f;
};
