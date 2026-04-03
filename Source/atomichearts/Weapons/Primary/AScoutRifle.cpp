// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/AScoutRifle.h"

AScoutRifle::AScoutRifle()
{
	WeaponName = FText::FromString("Chrome SR-1");
	WeaponDescription = FText::FromString("High-precision scout rifle. Ideal for marking targets and long-range elimination.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 75.f;
	Stats.FireRate = 0.8f;
	Stats.Range = 9000.f;
	Stats.Accuracy = 0.95f;
	Stats.HeadshotMultiplier = 3.0f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 15000.f;

	MagazineSize = 8;
	MaxReserveAmmo = 32;
	FireRate = 0.8f;

	ZoomedFOV = 20.f;
	ScopeZoomFOV = 20.f;

	NeonColor = FLinearColor(0.6f, 0.6f, 0.8f, 1.0f);
	Manufacturer = FText::FromString("Chrome Corporation");
	ModelDesignation = FText::FromString("SR-1");
	TechRank = 2;
	AIEngagementRange = 7000.f;
	AIAccuracy = 0.92f;
}

void AScoutRifle::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
