// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "GhostDetective9.generated.h"

/**
 * AGhostDetective9 — Ghost Detective-9 "Witness"
 * Compact suppressed pistol. Intelligence operatives' sidearm.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AGhostDetective9 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AGhostDetective9();

protected:
	virtual void BeginPlay() override;
};
