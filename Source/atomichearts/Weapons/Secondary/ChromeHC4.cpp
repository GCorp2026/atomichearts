// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/ChromeHC4.h"

AChromeHC4::AChromeHC4()
{
	WeaponName = FText::FromString("Chrome HC-4 Commander");
	WeaponDescription = FText::FromString("Military officer's sidearm. Chrome-plated with superior accuracy.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 42.f;
	Stats.FireRate = 0.25f;
	Stats.Range = 2600.f;
	Stats.Accuracy = 0.85f;
	Stats.HeadshotMultiplier = 2.2f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 4000.f;

	MagazineSize = 12;
	MaxReserveAmmo = 60;
	FireRate = 0.25f;

	NeonColor = FLinearColor(0.7f, 0.7f, 0.8f, 1.0f);
	Manufacturer = FText::FromString("Chrome Military");
	ModelDesignation = FText::FromString("HC-4");
	TechRank = 2;
	AIEngagementRange = 1600.f;
	AIAccuracy = 0.78.f;
}

void AChromeHC4::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
