// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AAutoRifle.generated.h"

/**
 * AAutoRifle — Axiom AR-7
 * High fire rate, moderate damage, fully automatic primary rifle.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AAutoRifle : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AAutoRifle();

protected:
	virtual void BeginPlay() override;
};
