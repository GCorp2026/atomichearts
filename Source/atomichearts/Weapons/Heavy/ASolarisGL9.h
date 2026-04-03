// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ASolarisGL9.generated.h"

/**
 * ASolarisGL9 — Solaris GL-9 "Nova"
 * Solar grenade launcher. Rounds detonate in blinding solar flashes.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ASolarisGL9 : public ACyberWeapon
{
	GENERATED_BODY()
public:
	ASolarisGL9();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, Category = "Grenade")
	float ExplosionRadius = 500.f;
	UPROPERTY(EditAnywhere, Category = "Grenade")
	float ProjectileSpeed = 1700.f;
};
