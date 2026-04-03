// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/DriftHC2.h"

ADriftHC2::ADriftHC2()
{
	WeaponName = FText::FromString("Drift HC-2 Madness");
	WeaponDescription = FText::FromString("Reality-fracturing pistol. Eldritch energies tear through dimensions.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Eldritch;

	Stats.Damage = 68.f;
	Stats.FireRate = 0.65f;
	Stats.Range = 2100.f;
	Stats.Accuracy = 0.66f;
	Stats.HeadshotMultiplier = 2.7f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 3700.f;

	MagazineSize = 6;
	MaxReserveAmmo = 30;
	FireRate = 0.65f;

	NeonColor = FLinearColor(0.8f, 0.0f, 1.0f, 1.0f);
	Manufacturer = FText::FromString("Drift Ordnance");
	ModelDesignation = FText::FromString("HC-2");
	TechRank = 3;
	AIEngagementRange = 1100.f;
	AIAccuracy = 0.62.f;
}

void ADriftHC2::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
