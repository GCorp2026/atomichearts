// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AAxiomCarbine5.generated.h"

/**
 * AAxiomCarbine5 — Axiom Carbine-5
 * Compact automatic carbine for tight spaces and fast movement.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AAxiomCarbine5 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AAxiomCarbine5();

protected:
	virtual void BeginPlay() override;
};
