// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AxiomPistolX.generated.h"

/**
 * AAxiomPistolX — Axiom Pistol-X "Officer"
 * Standard corporate sidearm. Reliable and accurate.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AAxiomPistolX : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AAxiomPistolX();

protected:
	virtual void BeginPlay() override;
};
