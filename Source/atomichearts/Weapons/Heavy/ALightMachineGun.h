// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ALightMachineGun.generated.h"

/**
 * ALightMachineGun — Axiom LMG-7
 * Suppressive fire weapon. High capacity, sustained fire at the cost of accuracy.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ALightMachineGun : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ALightMachineGun();

protected:
	virtual void BeginPlay() override;

public:
	// Suppression radius applied to enemies in area
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LMG")
	float SuppressionRadius = 400.f;
};
