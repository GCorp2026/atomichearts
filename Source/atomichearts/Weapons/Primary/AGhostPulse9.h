// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AGhostPulse9.generated.h"

/**
 * AGhostPulse9 — Ghost Pulse-9 "Glitch"
 * Energy pulse weapon that disrupts enemy systems and electronics on hit.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AGhostPulse9 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AGhostPulse9();

protected:
	virtual void BeginPlay() override;
};
