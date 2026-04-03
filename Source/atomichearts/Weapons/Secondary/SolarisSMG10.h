// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "SolarisSMG10.generated.h"

/**
 * ASolarisSMG10 — Solaris SMG-10 "Photon"
 * Light energy SMG. Rapid-fire solar projectiles.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ASolarisSMG10 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ASolarisSMG10();

protected:
	virtual void BeginPlay() override;
};
