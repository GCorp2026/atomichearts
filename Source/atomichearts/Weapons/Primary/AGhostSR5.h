// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AGhostSR5.generated.h"

/**
 * AGhostSR5 — Ghost SR-5 "Phantom"
 * Stealth rifle designed for silent elimination. Low tracers, maximum lethality.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AGhostSR5 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AGhostSR5();

protected:
	virtual void BeginPlay() override;
};
