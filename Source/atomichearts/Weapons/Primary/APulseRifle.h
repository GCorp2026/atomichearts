// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "APulseRifle.generated.h"

/**
 * APulseRifle — Neon PR-3
 * Energy-based rifle firing pulse rounds. Good accuracy, moderate damage.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API APulseRifle : public ACyberWeapon
{
	GENERATED_BODY()

public:
	APulseRifle();

protected:
	virtual void BeginPlay() override;
};
