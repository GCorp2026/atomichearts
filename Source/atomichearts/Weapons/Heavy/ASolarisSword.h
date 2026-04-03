// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ASolarisSword.generated.h"

/**
 * ASolarisSword — Solaris Sword-12 "Corona"
 * Solar energy blade. Leaves burning plasma trails.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ASolarisSword : public ACyberWeapon
{
	GENERATED_BODY()
public:
	ASolarisSword();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, Category = "Sword")
	float SlashArcAngle = 105.f;
	UPROPERTY(EditAnywhere, Category = "Sword")
	float StrikeReach = 260.f;
	UPROPERTY(EditAnywhere, Category = "Sword")
	float SlashDamageMultiplier = 1.7f;
	UPROPERTY(EditAnywhere, Category = "Sword")
	bool bHasChargeAttack = true;
	UPROPERTY(EditAnywhere, Category = "Sword", meta = (EditCondition = "bHasChargeAttack"))
	float ChargedAttackDamage = 180.f;
};
