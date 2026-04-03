// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/AChromeAR11.h"

AChromeAR11::AChromeAR11()
{
	WeaponName = FText::FromString("Chrome AR-11 \"Patriot\"");
	WeaponDescription = FText::FromString("Standard-issue Chrome military rifle. Balanced stats make it deadly in any situation.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 24.f;
	Stats.FireRate = 0.09f;
	Stats.Range = 5000.f;
	Stats.Accuracy = 0.84f;
	Stats.HeadshotMultiplier = 2.0f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 9000.f;

	MagazineSize = 30;
	MaxReserveAmmo = 150;
	FireRate = 0.09f;

	NeonColor = FLinearColor(0.5f, 0.6f, 0.9f, 1.0f);
	Manufacturer = FText::FromString("Chrome Corporation");
	ModelDesignation = FText::FromString("AR-11");
	TechRank = 1;
	AIEngagementRange = 4000.f;
	AIAccuracy = 0.82f;
}

void AChromeAR11::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
