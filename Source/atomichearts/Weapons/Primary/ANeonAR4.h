// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ANeonAR4.generated.h"

/**
 * ANeonAR4 — Neon AR-4 "Street Sweeper"
 * Close-range automatic rifle. High damage output in tight quarters.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ANeonAR4 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ANeonAR4();

protected:
	virtual void BeginPlay() override;
};
