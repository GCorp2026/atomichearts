// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ASolarisLMG.generated.h"

/**
 * ASolarisLMG — Solaris LMG-8 "Flare"
 * Heat-based heavy machine gun. Rounds ignite targets.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ASolarisLMG : public ACyberWeapon
{
	GENERATED_BODY()
public:
	ASolarisLMG();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LMG")
	float SuppressionRadius = 480.f;
	UPROPERTY(EditAnywhere, Category = "LMG")
	float IgniteChance = 0.25f;
};
