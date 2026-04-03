// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AHandCannon.generated.h"

/**
 * AHandCannon — Syndicate HC-9
 * High-damage pistol with low fire rate. Devastating at close range.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AHandCannon : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AHandCannon();

protected:
	virtual void BeginPlay() override;
};
