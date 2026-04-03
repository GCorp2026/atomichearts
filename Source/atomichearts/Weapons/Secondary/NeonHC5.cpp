// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/NeonHC5.h"

ANeonHC5::ANeonHC5()
{
	WeaponName = FText::FromString("Neon HC-5 Thug");
	WeaponDescription = FText::FromString("Street-grade heavy pistol. Reliable and affordable for syndicate enforcers.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 48.f;
	Stats.FireRate = 0.45f;
	Stats.Range = 1800.f;
	Stats.Accuracy = 0.60f;
	Stats.HeadshotMultiplier = 2.0f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 3000.f;

	MagazineSize = 10;
	MaxReserveAmmo = 50;
	FireRate = 0.45f;

	NeonColor = FLinearColor(1.0f, 0.0f, 0.5f, 1.0f);
	Manufacturer = FText::FromString("Neon Arms");
	ModelDesignation = FText::FromString("HC-5");
	TechRank = 0;
	AIEngagementRange = 1000.f;
	AIAccuracy = 0.58.f;
}

void ANeonHC5::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
