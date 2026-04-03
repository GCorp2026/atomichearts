// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AxiomLMG12.generated.h"

/**
 * CAxiomLMG12 — Axiom LMG-12 "Suppressor"
 * Extended barrel LMG for sustained suppressive fire.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API CAxiomLMG12 : public ACyberWeapon
{
	GENERATED_BODY()
public:
	CAxiomLMG12();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LMG")
	float SuppressionRadius = 500.f;
};
