// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ASolarisPulse11.generated.h"

/**
 * ASolarisPulse11 — Solaris Pulse-11 "Eclipse"
 * High-output solar pulse rifle. Unleashes concentrated solar bursts.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ASolarisPulse11 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ASolarisPulse11();

protected:
	virtual void BeginPlay() override;
};
