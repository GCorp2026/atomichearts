// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/ADriftLMG6.h"

ADriftLMG6::ADriftLMG6()
{
	WeaponName = FText::FromString("Drift LMG-6 \"Void\"");
	WeaponDescription = FText::FromString("Void-cannons that phase through solid matter. Rounds destabilize targets at a molecular level.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Plasma;

	Stats.Damage = 19.f;
	Stats.FireRate = 0.07f;
	Stats.Range = 5200.f;
	Stats.Accuracy = 0.55f;
	Stats.HeadshotMultiplier = 2.0f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 7800.f;

	MagazineSize = 95;
	MaxReserveAmmo = 190;
	FireRate = 0.07f;

	SuppressionRadius = 460.f;

	NeonColor = FLinearColor(0.5f, 0.0f, 1.0f, 1.0f);
	EnergyColor = FLinearColor(0.3f, 0.0f, 0.8f, 1.0f);
	Manufacturer = FText::FromString("Drift Collective");
	ModelDesignation = FText::FromString("LMG-6");
	TechRank = 2;
	AIEngagementRange = 4000.f;
	AIAccuracy = 0.50f;
}

void ADriftLMG6::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
