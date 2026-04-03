// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AxiomGL4.generated.h"

/**
 * CAxiomGL4 — Axiom GL-4 "Grenade Launcher"
 * Underbarrel explosive grenade launcher.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API CAxiomGL4 : public ACyberWeapon
{
	GENERATED_BODY()
public:
	CAxiomGL4();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, Category = "Grenade")
	float ExplosionRadius = 400.f;
	UPROPERTY(EditAnywhere, Category = "Grenade")
	float ProjectileSpeed = 1500.f;
};
