// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/AHeavySword.h"

AHeavySword::AHeavySword()
{
	WeaponName = FText::FromString("Axiom Sword-X \"Executioner\"");
	WeaponDescription = FText::FromString("Massive power blade. Charged attacks cleave through armor and deal bonus damage.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Plasma;

	Stats.Damage = 100.f;
	Stats.FireRate = 0.6f;
	Stats.Range = 250.f;
	Stats.Accuracy = 1.0f;
	Stats.HeadshotMultiplier = 1.0f;
	Stats.LegshotMultiplier = 1.0f;
	Stats.MaxRange = 350.f;

	MagazineSize = 1;
	MaxReserveAmmo = 0;
	FireRate = 0.6f;

	SlashArcAngle = 110.f;
	StrikeReach = 250.f;
	SlashDamageMultiplier = 1.6f;
	bHasChargeAttack = true;
	ChargedAttackDamage = 160.f;

	NeonColor = FLinearColor(1.0f, 0.1f, 0.0f, 1.0f);
	EnergyColor = FLinearColor(1.0f, 0.5f, 0.0f, 1.0f);
	Manufacturer = FText::FromString("Axiom Industries");
	ModelDesignation = FText::FromString("Sword-X");
	TechRank = 1;
	AIEngagementRange = 350.f;
	AIAccuracy = 0.95f;
}

void AHeavySword::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
