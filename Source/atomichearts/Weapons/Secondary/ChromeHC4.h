// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ChromeHC4.generated.h"

/**
 * AChromeHC4 — Chrome HC-4 "Commander"
 * Military officer's sidearm. Premium chrome finish.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AChromeHC4 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AChromeHC4();

protected:
	virtual void BeginPlay() override;
};
