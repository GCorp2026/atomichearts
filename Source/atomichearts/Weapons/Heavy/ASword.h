// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ASword.generated.h"

/**
 * ASword — Chrome Blade
 * Energy melee weapon. Slashes deal plasma damage in a short arc.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ASword : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ASword();

protected:
	virtual void BeginPlay() override;

public:
	// Arc angle for the slash (degrees)
	UPROPERTY(EditAnywhere, Category = "Sword")
	float SlashArcAngle = 90.f;

	// Reach of the sword strike
	UPROPERTY(EditAnywhere, Category = "Sword")
	float StrikeReach = 200.f;

	// Slash damage multiplier
	UPROPERTY(EditAnywhere, Category = "Sword")
	float SlashDamageMultiplier = 1.5f;

	// Does the sword have a charge attack?
	UPROPERTY(EditAnywhere, Category = "Sword")
	bool bHasChargeAttack = true;

	// Charge attack max damage
	UPROPERTY(EditAnywhere, Category = "Sword", meta = (EditCondition = "bHasChargeAttack"))
	float ChargedAttackDamage = 120.f;
};
