// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ANeonSMG8.generated.h"

/**
 * ANeonSMG8 — Neon SMG-8 "Viper"
 * Ultra-fast submachine gun. Burns through magazines at extreme speed.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ANeonSMG8 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ANeonSMG8();

protected:
	virtual void BeginPlay() override;
};
