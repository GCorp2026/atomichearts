// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "DriftShotgun6.generated.h"

/**
 * ADriftShotgun6 — Drift Shotgun-6 "Rift"
 * Void scatter weapon. Eldritch pellets tear through space.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ADriftShotgun6 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ADriftShotgun6();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Shotgun")
	int32 PelletCount = 10;

	UPROPERTY(EditAnywhere, Category = "Shotgun")
	float SpreadAngle = 22.f;
};
