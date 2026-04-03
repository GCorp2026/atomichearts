// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/AChromeMarksman3.h"

AChromeMarksman3::AChromeMarksman3()
{
	WeaponName = FText::FromString("Chrome Marksman-3");
	WeaponDescription = FText::FromString("Semi-auto precision rifle. Trained marksmen deliver lethal headshots.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 55.f;
	Stats.FireRate = 0.25f;
	Stats.Range = 8500.f;
	Stats.Accuracy = 0.96f;
	Stats.HeadshotMultiplier = 3.2f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 13000.f;

	MagazineSize = 10;
	MaxReserveAmmo = 40;
	FireRate = 0.25f;

	NeonColor = FLinearColor(0.55f, 0.6f, 0.95f, 1.0f);
	Manufacturer = FText::FromString("Chrome Corporation");
	ModelDesignation = FText::FromString("Marksman-3");
	TechRank = 2;
	AIEngagementRange = 7000.f;
	AIAccuracy = 0.93f;
}

void AChromeMarksman3::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
