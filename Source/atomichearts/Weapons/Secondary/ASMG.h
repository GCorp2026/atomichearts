// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ASMG.generated.h"

/**
 * ASMG — Ghost SMG-2
 * Fast-firing, low-damage secondary for close quarters.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ASMG : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ASMG();

protected:
	virtual void BeginPlay() override;
};
