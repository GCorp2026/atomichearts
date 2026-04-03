// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AxiomRevolver7.generated.h"

/**
 * AAxiomRevolver7 — Axiom Revolver-7 "Judge"
 * Six-shot revolver. High damage per round, slow reload.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AAxiomRevolver7 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AAxiomRevolver7();

protected:
	virtual void BeginPlay() override;
};
