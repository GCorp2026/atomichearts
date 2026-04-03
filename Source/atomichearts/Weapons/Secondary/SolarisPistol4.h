// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "SolarisPistol4.generated.h"

/**
 * ASolarisPistol4 — Solaris Pistol-4 "Flare"
 * Heat-round pistol. Incendiary ammunition for energy faction.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ASolarisPistol4 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ASolarisPistol4();

protected:
	virtual void BeginPlay() override;
};
