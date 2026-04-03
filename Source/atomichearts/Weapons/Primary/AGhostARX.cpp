// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/AGhostARX.h"

AGhostARX::AGhostARX()
{
	WeaponName = FText::FromString("Ghost AR-X \"Cipher\"");
	WeaponDescription = FText::FromString("Encrypted ballistic rifle. Bypasses shield harmonics for raw damage.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 27.f;
	Stats.FireRate = 0.08f;
	Stats.Range = 5500.f;
	Stats.Accuracy = 0.83f;
	Stats.HeadshotMultiplier = 2.1f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 9500.f;

	MagazineSize = 32;
	MaxReserveAmmo = 128;
	FireRate = 0.08f;

	NeonColor = FLinearColor(0.4f, 0.1f, 0.7f, 1.0f);
	Manufacturer = FText::FromString("Ghost Networks");
	ModelDesignation = FText::FromString("AR-X");
	TechRank = 2;
	AIEngagementRange = 4000.f;
	AIAccuracy = 0.80f;
}

void AGhostARX::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
