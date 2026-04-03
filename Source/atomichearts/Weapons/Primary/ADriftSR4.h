// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "ADriftSR4.generated.h"

/**
 * ADriftSR4 — Drift SR-4 "Void"
 * Reality-bending sniper rifle. Shots phase through dimensions before striking.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API ADriftSR4 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	ADriftSR4();

protected:
	virtual void BeginPlay() override;
};
