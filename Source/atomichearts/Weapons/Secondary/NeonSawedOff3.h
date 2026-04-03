// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "NeonSawedOff3.generated.h"

/**
 * ANeonSawedOff3 — Neon Sawed-Off-3 "Street"
 * Cut-down shotgun. Brutal close-range devastation.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ANeonSawedOff3 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ANeonSawedOff3();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Shotgun")
	int32 PelletCount = 6;

	UPROPERTY(EditAnywhere, Category = "Shotgun")
	float SpreadAngle = 25.f;
};
