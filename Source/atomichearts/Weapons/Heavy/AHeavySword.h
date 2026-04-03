// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AHeavySword.generated.h"

/**
 * AHeavySword — Axiom Sword-X "Executioner"
 * Heavy power blade with devastating charged strikes.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AHeavySword : public ACyberWeapon
{
	GENERATED_BODY()
public:
	AHeavySword();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, Category = "Sword")
	float SlashArcAngle = 110.f;
	UPROPERTY(EditAnywhere, Category = "Sword")
	float StrikeReach = 250.f;
	UPROPERTY(EditAnywhere, Category = "Sword")
	float SlashDamageMultiplier = 1.6f;
	UPROPERTY(EditAnywhere, Category = "Sword")
	bool bHasChargeAttack = true;
	UPROPERTY(EditAnywhere, Category = "Sword", meta = (EditCondition = "bHasChargeAttack"))
	float ChargedAttackDamage = 160.f;
};
