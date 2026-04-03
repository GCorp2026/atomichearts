// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/ANeonSword.h"

ANeonSword::ANeonSword()
{
	WeaponName = FText::FromString("Neon Sword-6 \"Blade\"");
	WeaponDescription = FText::FromString("Electrified neon katana. Fast wide-arcing slashes leave trails of pink plasma.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Plasma;

	Stats.Damage = 70.f;
	Stats.FireRate = 0.35f;
	Stats.Range = 220.f;
	Stats.Accuracy = 1.0f;
	Stats.HeadshotMultiplier = 1.0f;
	Stats.LegshotMultiplier = 1.0f;
	Stats.MaxRange = 320.f;

	MagazineSize = 1;
	MaxReserveAmmo = 0;
	FireRate = 0.35f;

	SlashArcAngle = 130.f;
	StrikeReach = 220.f;
	SlashDamageMultiplier = 1.4f;
	bHasChargeAttack = false;

	NeonColor = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f);
	EnergyColor = FLinearColor(0.8f, 0.0f, 1.0f, 1.0f);
	Manufacturer = FText::FromString("Neon Syndicate");
	ModelDesignation = FText::FromString("Sword-6");
	TechRank = 0;
	AIEngagementRange = 320.f;
	AIAccuracy = 0.90f;
}

void ANeonSword::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
