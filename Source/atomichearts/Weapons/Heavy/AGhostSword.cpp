// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/AGhostSword.h"

AGhostSword::AGhostSword()
{
	WeaponName = FText::FromString("Ghost Sword-8 \"Data\"");
	WeaponDescription = FText::FromString("Hardlight energy blade. Phases through shields and deals bonus damage to machines.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Plasma;

	Stats.Damage = 90.f;
	Stats.FireRate = 0.45f;
	Stats.Range = 280.f;
	Stats.Accuracy = 0.95f;
	Stats.HeadshotMultiplier = 1.0f;
	Stats.LegshotMultiplier = 1.0f;
	Stats.MaxRange = 380.f;

	MagazineSize = 1;
	MaxReserveAmmo = 0;
	FireRate = 0.45f;

	SlashArcAngle = 100.f;
	StrikeReach = 280.f;
	SlashDamageMultiplier = 1.5f;
	bHasChargeAttack = true;
	ChargedAttackDamage = 150.f;

	NeonColor = FLinearColor(0.0f, 1.0f, 0.5f, 1.0f);
	EnergyColor = FLinearColor(0.5f, 1.0f, 0.8f, 1.0f);
	Manufacturer = FText::FromString("Ghost Collective");
	ModelDesignation = FText::FromString("Sword-8");
	TechRank = 2;
	AIEngagementRange = 380.f;
	AIAccuracy = 0.93f;
}

void AGhostSword::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
