// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/AHandCannon.h"

AHandCannon::AHandCannon()
{
	WeaponName = FText::FromString("Syndicate HC-9");
	WeaponDescription = FText::FromString("Heavy cyber-pistol. Fires oversized rounds that tear through armor.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 65.f;
	Stats.FireRate = 0.6f;
	Stats.Range = 2500.f;
	Stats.Accuracy = 0.70f;
	Stats.HeadshotMultiplier = 2.5f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 4000.f;

	MagazineSize = 6;
	MaxReserveAmmo = 36;
	FireRate = 0.6f;

	NeonColor = FLinearColor(1.0f, 0.2f, 0.1f, 1.0f);
	Manufacturer = FText::FromString("Syndicate Arms");
	ModelDesignation = FText::FromString("HC-9");
	TechRank = 1;
	AIEngagementRange = 1500.f;
	AIAccuracy = 0.65f;
}

void AHandCannon::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
