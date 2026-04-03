// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AChromeAR11.generated.h"

/**
 * AChromeAR11 — Chrome AR-11 "Patriot"
 * Standard-issue assault rifle for Chrome military forces. Reliable and balanced.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AChromeAR11 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AChromeAR11();

protected:
	virtual void BeginPlay() override;
};
