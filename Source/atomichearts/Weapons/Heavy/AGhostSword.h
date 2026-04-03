// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AGhostSword.generated.h"

/**
 * AGhostSword — Ghost Sword-8 "Data"
 * Hardlight blade that phases through shields.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AGhostSword : public ACyberWeapon
{
	GENERATED_BODY()
public:
	AGhostSword();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, Category = "Sword")
	float SlashArcAngle = 100.f;
	UPROPERTY(EditAnywhere, Category = "Sword")
	float StrikeReach = 280.f;
	UPROPERTY(EditAnywhere, Category = "Sword")
	float SlashDamageMultiplier = 1.5f;
	UPROPERTY(EditAnywhere, Category = "Sword")
	bool bHasChargeAttack = true;
	UPROPERTY(EditAnywhere, Category = "Sword", meta = (EditCondition = "bHasChargeAttack"))
	float ChargedAttackDamage = 150.f;
};
