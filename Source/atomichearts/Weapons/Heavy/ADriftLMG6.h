// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ADriftLMG6.generated.h"

/**
 * ADriftLMG6 — Drift LMG-6 "Void"
 * Void energy heavy machine gun. Rounds phase through matter.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ADriftLMG6 : public ACyberWeapon
{
	GENERATED_BODY()
public:
	ADriftLMG6();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LMG")
	float SuppressionRadius = 460.f;
};
