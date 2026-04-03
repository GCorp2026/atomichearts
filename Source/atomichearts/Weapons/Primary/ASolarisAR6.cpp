// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/ASolarisAR6.h"

ASolarisAR6::ASolarisAR6()
{
	WeaponName = FText::FromString("Solaris AR-6 \"Radiant\"");
	WeaponDescription = FText::FromString("Solar energy assault rifle. Concentrated photons reduce targets to ash.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Energy;

	Stats.Damage = 21.f;
	Stats.FireRate = 0.06f;
	Stats.Range = 4500.f;
	Stats.Accuracy = 0.80f;
	Stats.HeadshotMultiplier = 2.2f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 7500.f;

	MagazineSize = 30;
	MaxReserveAmmo = 120;
	FireRate = 0.06f;

	NeonColor = FLinearColor(1.0f, 0.8f, 0.0f, 1.0f);
	EnergyColor = FLinearColor(1.0f, 0.9f, 0.2f, 1.0f);
	Manufacturer = FText::FromString("Solaris Energy Corp");
	ModelDesignation = FText::FromString("AR-6");
	TechRank = 2;
	AIEngagementRange = 3200.f;
	AIAccuracy = 0.78f;
}

void ASolarisAR6::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
