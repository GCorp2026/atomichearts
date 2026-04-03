// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/ChromeRevolver2.h"

AChromeRevolver2::AChromeRevolver2()
{
	WeaponName = FText::FromString("Chrome Revolver-2 Marshal");
	WeaponDescription = FText::FromString("Military lawman revolver. Reliable six-shot with heavy rounds.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 58.f;
	Stats.FireRate = 0.55f;
	Stats.Range = 3000.f;
	Stats.Accuracy = 0.78f;
	Stats.HeadshotMultiplier = 2.5f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 4500.f;

	MagazineSize = 6;
	MaxReserveAmmo = 36;
	FireRate = 0.55f;

	NeonColor = FLinearColor(0.6f, 0.6f, 0.7f, 1.0f);
	Manufacturer = FText::FromString("Chrome Military");
	ModelDesignation = FText::FromString("Revolver-2");
	TechRank = 2;
	AIEngagementRange = 2000.f;
	AIAccuracy = 0.72.f;
}

void AChromeRevolver2::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
