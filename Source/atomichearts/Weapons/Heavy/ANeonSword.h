// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ANeonSword.generated.h"

/**
 * ANeonSword — Neon Sword-6 "Blade"
 * Neon katana with electrified edge and wide slash arc.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ANeonSword : public ACyberWeapon
{
	GENERATED_BODY()
public:
	ANeonSword();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, Category = "Sword")
	float SlashArcAngle = 130.f;
	UPROPERTY(EditAnywhere, Category = "Sword")
	float StrikeReach = 220.f;
	UPROPERTY(EditAnywhere, Category = "Sword")
	float SlashDamageMultiplier = 1.4f;
	UPROPERTY(EditAnywhere, Category = "Sword")
	bool bHasChargeAttack = false;
};
