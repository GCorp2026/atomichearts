// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "NeonMachinePistol8.generated.h"

/**
 * ANeonMachinePistol8 — Neon MachinePistol-8 "FullAuto"
 * Full-auto guncaster pistol. Burns through ammo fast.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ANeonMachinePistol8 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ANeonMachinePistol8();

protected:
	virtual void BeginPlay() override;
};
