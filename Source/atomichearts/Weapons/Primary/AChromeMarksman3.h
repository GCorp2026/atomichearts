// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AChromeMarksman3.generated.h"

/**
 * AChromeMarksman3 — Chrome Marksman-3
 * Semi-automatic precision rifle. Each shot counts with surgical accuracy.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AChromeMarksman3 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AChromeMarksman3();

protected:
	virtual void BeginPlay() override;
};
