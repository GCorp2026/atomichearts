// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AAxiomAR9.generated.h"

/**
 * AAxiomAR9 — Axiom AR-9 "Overkill"
 * Full-auto urban combat rifle. High volume of fire, designed for room clearing.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AAxiomAR9 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AAxiomAR9();

protected:
	virtual void BeginPlay() override;
};
