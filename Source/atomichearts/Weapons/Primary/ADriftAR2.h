// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ADriftAR2.generated.h"

/**
 * ADriftAR2 — Drift AR-2 "Abyss"
 * Void energy assault rifle. Channels cosmic entropy into devastating rounds.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ADriftAR2 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ADriftAR2();

protected:
	virtual void BeginPlay() override;
};
