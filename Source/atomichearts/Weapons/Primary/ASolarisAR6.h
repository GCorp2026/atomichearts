// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ASolarisAR6.generated.h"

/**
 * ASolarisAR6 — Solaris AR-6 "Radiant"
 * Solar-powered automatic rifle. Burns with concentrated photonic energy.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ASolarisAR6 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ASolarisAR6();

protected:
	virtual void BeginPlay() override;
};
