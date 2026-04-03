// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/SolarisPistol4.h"

ASolarisPistol4::ASolarisPistol4()
{
	WeaponName = FText::FromString("Solaris Pistol-4 Flare");
	WeaponDescription = FText::FromString("Incendiary heat-round pistol. Burns through shields with solar energy.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Energy;

	Stats.Damage = 32.f;
	Stats.FireRate = 0.2f;
	Stats.Range = 2200.f;
	Stats.Accuracy = 0.78f;
	Stats.HeadshotMultiplier = 2.0f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 3600.f;

	MagazineSize = 14;
	MaxReserveAmmo = 70;
	FireRate = 0.2f;

	NeonColor = FLinearColor(1.0f, 0.8f, 0.0f, 1.0f);
	Manufacturer = FText::FromString("Solaris Tech");
	ModelDesignation = FText::FromString("Pistol-4");
	TechRank = 2;
	AIEngagementRange = 1400.f;
	AIAccuracy = 0.70.f;
}

void ASolarisPistol4::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
