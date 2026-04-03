// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AScoutRifle.generated.h"

/**
 * AScoutRifle — Chrome SR-1
 * Precise, slow-firing rifle for long-range engagements.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AScoutRifle : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AScoutRifle();

protected:
	virtual void BeginPlay() override;

public:
	// Scope zoom level when aiming
	UPROPERTY(EditAnywhere, Category = "Scout")
	float ScopeZoomFOV = 20.f;
};
