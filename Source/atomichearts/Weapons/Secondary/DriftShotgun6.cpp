// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/DriftShotgun6.h"

ADriftShotgun6::ADriftShotgun6()
{
	WeaponName = FText::FromString("Drift Shotgun-6 Rift");
	WeaponDescription = FText::FromString("Void scatter shotgun. Eldritch pellets phase through reality.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Eldritch;

	Stats.Damage = 16.f;
	Stats.FireRate = 0.85f;
	Stats.Range = 700.f;
	Stats.Accuracy = 0.38f;
	Stats.HeadshotMultiplier = 1.4f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 1400.f;

	MagazineSize = 5;
	MaxReserveAmmo = 25;
	FireRate = 0.85f;

	PelletCount = 10;
	SpreadAngle = 22.f;

	NeonColor = FLinearColor(0.6f, 0.0f, 0.8f, 1.0f);
	Manufacturer = FText::FromString("Drift Ordnance");
	ModelDesignation = FText::FromString("Shotgun-6");
	TechRank = 2;
	AIEngagementRange = 700.f;
	AIAccuracy = 0.48.f;
}

void ADriftShotgun6::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
