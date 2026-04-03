// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AAxiomPulse3.generated.h"

/**
 * AAxiomPulse3 — Axiom Pulse-3 "Mainframe"
 * Smart-pulse energy rifle. Features targeting assists and predictive tracking.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AAxiomPulse3 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AAxiomPulse3();

protected:
	virtual void BeginPlay() override;
};
