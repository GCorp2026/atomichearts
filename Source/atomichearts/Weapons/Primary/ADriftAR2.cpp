// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/ADriftAR2.h"

ADriftAR2::ADriftAR2()
{
	WeaponName = FText::FromString("Drift AR-2 \"Abyss\"");
	WeaponDescription = FText::FromString("Void energy assault rifle. Channels cosmic entropy into devastating firepower.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Plasma;

	Stats.Damage = 30.f;
	Stats.FireRate = 0.07f;
	Stats.Range = 5000.f;
	Stats.Accuracy = 0.81f;
	Stats.HeadshotMultiplier = 2.4f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 8500.f;

	MagazineSize = 25;
	MaxReserveAmmo = 100;
	FireRate = 0.07f;

	NeonColor = FLinearColor(0.5f, 0.0f, 0.4f, 1.0f);
	EnergyColor = FLinearColor(0.7f, 0.0f, 0.6f, 1.0f);
	Manufacturer = FText::FromString("Drift Collective");
	ModelDesignation = FText::FromString("AR-2");
	TechRank = 3;
	AIEngagementRange = 3800.f;
	AIAccuracy = 0.79f;
}

void ADriftAR2::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
