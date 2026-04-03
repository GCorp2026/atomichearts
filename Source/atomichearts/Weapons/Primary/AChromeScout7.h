// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AChromeScout7.generated.h"

/**
 * AChromeScout7 — Chrome Scout-7 "Eagle Eye"
 * Extended-range scout rifle for precision elimination at extreme distances.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AChromeScout7 : public ACyberWeapon
{
	GENERATED_BODY()

public:
	AChromeScout7();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Scout")
	float ScopeZoomFOV = 18.f;
};
