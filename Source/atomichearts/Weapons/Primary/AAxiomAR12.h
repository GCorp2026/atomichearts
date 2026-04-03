// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AAxiomAR12.generated.h"

/**
 * AAxiomAR12 — Axiom AR-12 "Protocol"
 * Burst-fire assault rifle. Three-round burst with high stopping power.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AAxiomAR12 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AAxiomAR12();

protected:
	virtual void BeginPlay() override;
};
