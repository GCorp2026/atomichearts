// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/ANeonAR4.h"

ANeonAR4::ANeonAR4()
{
	WeaponName = FText::FromString("Neon AR-4 \"Street Sweeper\"");
	WeaponDescription = FText::FromString("Close-range assault rifle. Built for room clearing and tight alleyways.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 25.f;
	Stats.FireRate = 0.07f;
	Stats.Range = 2800.f;
	Stats.Accuracy = 0.70f;
	Stats.HeadshotMultiplier = 2.0f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 4500.f;

	MagazineSize = 35;
	MaxReserveAmmo = 140;
	FireRate = 0.07f;

	NeonColor = FLinearColor(1.0f, 0.0f, 0.8f, 1.0f);
	Manufacturer = FText::FromString("Neon Tech Labs");
	ModelDesignation = FText::FromString("AR-4");
	TechRank = 1;
	AIEngagementRange = 1800.f;
	AIAccuracy = 0.65f;
}

void ANeonAR4::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
