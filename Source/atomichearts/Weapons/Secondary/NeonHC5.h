// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "NeonHC5.generated.h"

/**
 * ANeonHC5 — Neon HC-5 "Thug"
 * Cheap reliable heavy pistol. Street-grade stopping power.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ANeonHC5 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ANeonHC5();

protected:
	virtual void BeginPlay() override;
};
