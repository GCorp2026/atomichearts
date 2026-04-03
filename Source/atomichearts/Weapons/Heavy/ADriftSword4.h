// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ADriftSword4.generated.h"

/**
 * ADriftSword4 — Drift Sword-4 "Madness"
 * Reality-warping blade from the Eldritch Drift. Bleeds sanity.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ADriftSword4 : public ACyberWeapon
{
	GENERATED_BODY()
public:
	ADriftSword4();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, Category = "Sword")
	float SlashArcAngle = 140.f;
	UPROPERTY(EditAnywhere, Category = "Sword")
	float StrikeReach = 240.f;
	UPROPERTY(EditAnywhere, Category = "Sword")
	float SlashDamageMultiplier = 1.8f;
	UPROPERTY(EditAnywhere, Category = "Sword")
	bool bHasChargeAttack = true;
	UPROPERTY(EditAnywhere, Category = "Sword", meta = (EditCondition = "bHasChargeAttack"))
	float ChargedAttackDamage = 200.f;
};
