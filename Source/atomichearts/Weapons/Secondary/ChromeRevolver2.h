// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ChromeRevolver2.generated.h"

/**
 * AChromeRevolver2 — Chrome Revolver-2 "Marshal"
 * Military lawman's revolver. Six shots of justice.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AChromeRevolver2 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AChromeRevolver2();

protected:
	virtual void BeginPlay() override;
};
