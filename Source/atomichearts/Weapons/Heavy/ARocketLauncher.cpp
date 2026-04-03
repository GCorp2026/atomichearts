// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/ARocketLauncher.h"

ARocketLauncher::ARocketLauncher()
{
	WeaponName = FText::FromString("Solaris RL-X");
	WeaponDescription = FText::FromString("Guided rocket launcher. Rockets deal massive area-of-effect damage.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Explosive;

	Stats.Damage = 150.f;
	Stats.FireRate = 1.5f;
	Stats.Range = 8000.f;
	Stats.Accuracy = 0.90f;
	Stats.HeadshotMultiplier = 1.0f;
	Stats.LegshotMultiplier = 1.0f;
	Stats.MaxRange = 10000.f;

	MagazineSize = 2;
	MaxReserveAmmo = 8;
	FireRate = 1.5f;

	ExplosionRadius = 500.f;
	RocketSpeed = 2000.f;
	bHomingRocket = true;

	NeonColor = FLinearColor(1.0f, 0.3f, 0.0f, 1.0f);
	EnergyColor = FLinearColor(1.0f, 0.6f, 0.0f, 1.0f);
	Manufacturer = FText::FromString("Solaris Defense");
	ModelDesignation = FText::FromString("RL-X");
	TechRank = 2;
	AIEngagementRange = 5000.f;
	AIAccuracy = 0.85f;
}

void ARocketLauncher::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
