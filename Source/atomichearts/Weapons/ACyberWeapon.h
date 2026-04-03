// Copyright 2026 Atomic Hearts Team

#pragma once

#include "Weapons/AWeaponBase.h"
#include "ACyberWeapon.generated.h"

/**
 * ACyberWeapon — base class for all Atomic Hearts cyberpunk-themed weapons.
 * Adds neon glow effects, energy ammo type, and cyber weapon visuals.
 */
UCLASS(Abstract, Blueprintable)
class ATOMICHEARTS_API ACyberWeapon : public AAWeaponBase
{
	GENERATED_BODY()

public:
	ACyberWeapon();

protected:
	virtual void BeginPlay() override;

public:
	// Neon glow color for this weapon (used by material instances)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cyber|VFX")
	FLinearColor NeonColor = FLinearColor(0.0f, 1.0f, 0.85f, 1.0f);

	// Energy color for beam/tracer effects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cyber|VFX")
	FLinearColor EnergyColor = FLinearColor(0.0f, 0.8f, 1.0f, 1.0f);

	// Should this weapon have a persistent neon glow?
	UPROPERTY(EditAnywhere, Category = "Cyber|VFX")
	bool bHasNeonGlow = true;

	// Electric buzz sound for energy weapons
	UPROPERTY(EditAnywhere, Category = "Cyber|Sound")
	TObjectPtr<USoundCue> EnergyChargeSound;

	// Cyber UI overlay tint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cyber|UI")
	FLinearColor HUDTint = FLinearColor(0.0f, 1.0f, 0.85f, 0.3f);

	// Tech rank: 0=common, 1=rare, 2=elite
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cyber")
	int32 TechRank = 0;

	// Manufacturer/corp name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cyber")
	FText Manufacturer = FText::FromString("Axiom Industries");

	// Model designation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cyber")
	FText ModelDesignation = FText::FromString("MK-I");

protected:
	// Apply neon glow to weapon mesh based on NeonColor
	UFUNCTION(BlueprintCallable, Category = "Cyber|VFX")
	void ApplyNeonGlow();

	// Remove neon glow from weapon mesh
	UFUNCTION(BlueprintCallable, Category = "Cyber|VFX")
	void RemoveNeonGlow();
};
