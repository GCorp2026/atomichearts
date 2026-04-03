// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "GhostHC3.generated.h"

/**
 * AGhostHC3 — Ghost HC-3 "Silent"
 * Whisper-quiet heavy pistol. Ghost operatives' concealed weapon.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AGhostHC3 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AGhostHC3();

protected:
	virtual void BeginPlay() override;
};
