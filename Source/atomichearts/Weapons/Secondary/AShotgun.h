// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AShotgun.generated.h"

/**
 * AShotgun — Drift SG-1
 * Close-range spread weapon. Massive damage up close, ineffective at range.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AShotgun : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AShotgun();

protected:
	virtual void BeginPlay() override;

public:
	// Number of pellets per shot
	UPROPERTY(EditAnywhere, Category = "Shotgun")
	int32 PelletCount = 8;

	// Spread angle in degrees
	UPROPERTY(EditAnywhere, Category = "Shotgun")
	float SpreadAngle = 15.f;
};
