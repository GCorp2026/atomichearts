// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "SolarisHC8.generated.h"

/**
 * ASolarisHC8 — Solaris HC-8 "Corona"
 * Solar burst heavy pistol. Concentrated energy discharge.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ASolarisHC8 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ASolarisHC8();

protected:
	virtual void BeginPlay() override;
};
