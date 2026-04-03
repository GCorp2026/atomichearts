// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "DriftHC2.generated.h"

/**
 * ADriftHC2 — Drift HC-2 "Madness"
 * Reality-fracturing heavy pistol. Eldritch weapon from beyond.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ADriftHC2 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ADriftHC2();

protected:
	virtual void BeginPlay() override;
};
