// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/SolarisSMG10.h"

ASolarisSMG10::ASolarisSMG10()
{
	WeaponName = FText::FromString("Solaris SMG-10 Photon");
	WeaponDescription = FText::FromString("Light-based SMG. Rapid photon bursts for sustained fire.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Energy;

	Stats.Damage = 12.f;
	Stats.FireRate = 0.04f;
	Stats.Range = 1900.f;
	Stats.Accuracy = 0.62f;
	Stats.HeadshotMultiplier = 1.7f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 3200.f;

	MagazineSize = 35;
	MaxReserveAmmo = 175;
	FireRate = 0.04f;

	NeonColor = FLinearColor(1.0f, 0.9f, 0.2f, 1.0f);
	Manufacturer = FText::FromString("Solaris Tech");
	ModelDesignation = FText::FromString("SMG-10");
	TechRank = 2;
	AIEngagementRange = 1100.f;
	AIAccuracy = 0.58.f;
}

void ASolarisSMG10::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
