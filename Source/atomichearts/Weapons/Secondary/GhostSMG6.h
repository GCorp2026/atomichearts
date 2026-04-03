// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "GhostSMG6.generated.h"

/**
 * AGhostSMG6 — Ghost SMG-6 "Invisible"
 * Suppressed submachine gun. Silent death from the shadows.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AGhostSMG6 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AGhostSMG6();

protected:
	virtual void BeginPlay() override;
};
