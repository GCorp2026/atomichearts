// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/AxiomPistolX.h"

AAxiomPistolX::AAxiomPistolX()
{
	WeaponName = FText::FromString("Axiom Pistol-X Officer");
	WeaponDescription = FText::FromString("Standard issue sidearm. Balanced performance for corporate officers.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 28.f;
	Stats.FireRate = 0.18f;
	Stats.Range = 2400.f;
	Stats.Accuracy = 0.82f;
	Stats.HeadshotMultiplier = 2.0f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 3500.f;

	MagazineSize = 12;
	MaxReserveAmmo = 60;
	FireRate = 0.18f;

	NeonColor = FLinearColor(0.0f, 0.7f, 0.9f, 1.0f);
	Manufacturer = FText::FromString("Axiom Industries");
	ModelDesignation = FText::FromString("Pistol-X");
	TechRank = 1;
	AIEngagementRange = 1400.f;
	AIAccuracy = 0.72.f;
}

void AAxiomPistolX::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
