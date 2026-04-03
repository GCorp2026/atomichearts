// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AxiomHC12.generated.h"

/**
 * AAxiomHC12 — Axiom HC-12 "Enforcer"
 * Heavy corporate pistol. Overclocked rounds for maximum damage.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AAxiomHC12 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AAxiomHC12();

protected:
	virtual void BeginPlay() override;
};
