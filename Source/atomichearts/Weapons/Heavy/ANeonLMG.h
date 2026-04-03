// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ANeonLMG.generated.h"

/**
 * ANeonLMG — Neon LMG-4 "Street"
 * Jury-rigged heavy machine gun built from scrap and neon tech.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ANeonLMG : public ACyberWeapon
{
	GENERATED_BODY()
public:
	ANeonLMG();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LMG")
	float SuppressionRadius = 380.f;
};
