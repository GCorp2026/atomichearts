// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "AGhostLMG.generated.h"

/**
 * AGhostLMG — Ghost LMG-3 "Ghost"
 * Ghost cell silent heavy machine gun. Suppressed fire, minimal trace.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API AGhostLMG : public ACyberWeapon
{
	GENERATED_BODY()
public:
	AGhostLMG();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LMG")
	float SuppressionRadius = 420.f;
};
