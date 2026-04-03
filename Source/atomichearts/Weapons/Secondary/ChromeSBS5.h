// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ChromeSBS5.generated.h"

/**
 * AChromeSBS5 — Chrome SBS-5 "Breacher"
 * Short-barrel shotgun. Entry weapon for military breachers.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AChromeSBS5 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AChromeSBS5();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Shotgun")
	int32 PelletCount = 8;

	UPROPERTY(EditAnywhere, Category = "Shotgun")
	float SpreadAngle = 20.f;
};
