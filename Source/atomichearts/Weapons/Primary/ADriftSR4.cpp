// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/ADriftSR4.h"

ADriftSR4::ADriftSR4()
{
	WeaponName = FText::FromString("Drift SR-4 \"Void\"");
	WeaponDescription = FText::FromString("Void sniper rifle. Reality bends as shots tear through dimensional barriers.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Plasma;

	Stats.Damage = 95.f;
	Stats.FireRate = 0.9f;
	Stats.Range = 13000.f;
	Stats.Accuracy = 0.97f;
	Stats.HeadshotMultiplier = 3.5f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 19000.f;

	MagazineSize = 4;
	MaxReserveAmmo = 16;
	FireRate = 0.9f;

	NeonColor = FLinearColor(0.4f, 0.0f, 0.6f, 1.0f);
	EnergyColor = FLinearColor(0.6f, 0.0f, 0.8f, 1.0f);
	Manufacturer = FText::FromString("Drift Collective");
	ModelDesignation = FText::FromString("SR-4");
	TechRank = 3;
	AIEngagementRange = 10000.f;
	AIAccuracy = 0.96f;
}

void ADriftSR4::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
