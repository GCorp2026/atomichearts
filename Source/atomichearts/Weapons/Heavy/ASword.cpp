// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/ASword.h"

ASword::ASword()
{
	WeaponName = FText::FromString("Chrome Blade");
	WeaponDescription = FText::FromString("Plasma-charged energy sword. Devastating melee weapon with charged attack capability.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Plasma;

	Stats.Damage = 80.f;
	Stats.FireRate = 0.5f;
	Stats.Range = 200.f;
	Stats.Accuracy = 1.0f;
	Stats.HeadshotMultiplier = 1.0f;
	Stats.LegshotMultiplier = 1.0f;
	Stats.MaxRange = 300.f;

	MagazineSize = 1;      // melee doesn't use traditional ammo
	MaxReserveAmmo = 0;
	FireRate = 0.5f;

	SlashArcAngle = 90.f;
	StrikeReach = 200.f;
	SlashDamageMultiplier = 1.5f;
	bHasChargeAttack = true;
	ChargedAttackDamage = 120.f;

	NeonColor = FLinearColor(0.3f, 0.8f, 1.0f, 1.0f);
	EnergyColor = FLinearColor(0.5f, 1.0f, 1.0f, 1.0f);
	Manufacturer = FText::FromString("Chrome Corporation");
	ModelDesignation = FText::FromString("Blade");
	TechRank = 2;
	AIEngagementRange = 300.f;
	AIAccuracy = 0.95f;
	AIEngagementRange = 300.f;
}

void ASword::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
