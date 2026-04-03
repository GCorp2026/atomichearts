// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/ACyberWeapon.h"
#include "CChromeLMG9.generated.h"

/**
 * CChromeLMG9 — Chrome LMG-9 "Duty"
 * Standard issue Chrome military heavy machine gun.
 */
UCLASS(Blueprintable)
class ATOMICHEARTS_API CChromeLMG9 : public ACyberWeapon
{
	GENERATED_BODY()
public:
	CChromeLMG9();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LMG")
	float SuppressionRadius = 550.f;
};
