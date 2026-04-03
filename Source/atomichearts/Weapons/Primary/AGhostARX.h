// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AGhostARX.generated.h"

/**
 * AGhostARX — Ghost AR-X "Cipher"
 * Assault rifle firing encrypted rounds that bypass enemy shield harmonics.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AGhostARX : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AGhostARX();

protected:
	virtual void BeginPlay() override;
};
