// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/ANeonCarbineX.h"

ANeonCarbineX::ANeonCarbineX()
{
	WeaponName = FText::FromString("Neon Carbine-X");
	WeaponDescription = FText::FromString("Hybrid carbine firing specialized rounds. Adapts to mid-range engagements.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 23.f;
	Stats.FireRate = 0.09f;
	Stats.Range = 4000.f;
	Stats.Accuracy = 0.80f;
	Stats.HeadshotMultiplier = 2.1f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 7000.f;

	MagazineSize = 32;
	MaxReserveAmmo = 128;
	FireRate = 0.09f;

	NeonColor = FLinearColor(0.9f, 0.0f, 0.5f, 1.0f);
	Manufacturer = FText::FromString("Neon Tech Labs");
	ModelDesignation = FText::FromString("Carbine-X");
	TechRank = 2;
	AIEngagementRange = 3000.f;
	AIAccuracy = 0.78f;
}

void ANeonCarbineX::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
