// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/ADriftSword4.h"

ADriftSword4::ADriftSword4()
{
	WeaponName = FText::FromString("Drift Sword-4 \"Madness\"");
	WeaponDescription = FText::FromString("Eldritch reality blade. Wide arcs slice through dimensions. Charged attack warps space.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Plasma;

	Stats.Damage = 95.f;
	Stats.FireRate = 0.55f;
	Stats.Range = 240.f;
	Stats.Accuracy = 1.0f;
	Stats.HeadshotMultiplier = 1.0f;
	Stats.LegshotMultiplier = 1.0f;
	Stats.MaxRange = 340.f;

	MagazineSize = 1;
	MaxReserveAmmo = 0;
	FireRate = 0.55f;

	SlashArcAngle = 140.f;
	StrikeReach = 240.f;
	SlashDamageMultiplier = 1.8f;
	bHasChargeAttack = true;
	ChargedAttackDamage = 200.f;

	NeonColor = FLinearColor(0.6f, 0.0f, 1.0f, 1.0f);
	EnergyColor = FLinearColor(0.4f, 0.0f, 0.8f, 1.0f);
	Manufacturer = FText::FromString("Drift Collective");
	ModelDesignation = FText::FromString("Sword-4");
	TechRank = 2;
	AIEngagementRange = 340.f;
	AIAccuracy = 0.90f;
}

void ADriftSword4::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
