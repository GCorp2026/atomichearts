// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ANeonCarbineX.generated.h"

/**
 * ANeonCarbineX — Neon Carbine-X
 * Hybrid carbine balancing ballistic and energy damage. Versatile for any fight.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ANeonCarbineX : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ANeonCarbineX();

protected:
	virtual void BeginPlay() override;
};
