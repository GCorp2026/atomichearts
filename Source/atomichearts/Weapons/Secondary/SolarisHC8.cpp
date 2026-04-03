// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/SolarisHC8.h"

ASolarisHC8::ASolarisHC8()
{
	WeaponName = FText::FromString("Solaris HC-8 Corona");
	WeaponDescription = FText::FromString("Solar burst heavy pistol. Concentrated solar energy for maximum damage.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Energy;

	Stats.Damage = 55.f;
	Stats.FireRate = 0.5f;
	Stats.Range = 2000.f;
	Stats.Accuracy = 0.72f;
	Stats.HeadshotMultiplier = 2.4f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 3400.f;

	MagazineSize = 8;
	MaxReserveAmmo = 40;
	FireRate = 0.5f;

	NeonColor = FLinearColor(1.0f, 0.6f, 0.0f, 1.0f);
	Manufacturer = FText::FromString("Solaris Tech");
	ModelDesignation = FText::FromString("HC-8");
	TechRank = 3;
	AIEngagementRange = 1300.f;
	AIAccuracy = 0.68.f;
}

void ASolarisHC8::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
