// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/ASolarisSword.h"

ASolarisSword::ASolarisSword()
{
	WeaponName = FText::FromString("Solaris Sword-12 \"Corona\"");
	WeaponDescription = FText::FromString("Solar energy blade. Corona-class sword burns targets with concentrated solar plasma.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Plasma;

	Stats.Damage = 110.f;
	Stats.FireRate = 0.5f;
	Stats.Range = 260.f;
	Stats.Accuracy = 1.0f;
	Stats.HeadshotMultiplier = 1.0f;
	Stats.LegshotMultiplier = 1.0f;
	Stats.MaxRange = 360.f;

	MagazineSize = 1;
	MaxReserveAmmo = 0;
	FireRate = 0.5f;

	SlashArcAngle = 105.f;
	StrikeReach = 260.f;
	SlashDamageMultiplier = 1.7f;
	bHasChargeAttack = true;
	ChargedAttackDamage = 180.f;

	NeonColor = FLinearColor(1.0f, 0.7f, 0.0f, 1.0f);
	EnergyColor = FLinearColor(1.0f, 0.9f, 0.2f, 1.0f);
	Manufacturer = FText::FromString("Solaris Defense");
	ModelDesignation = FText::FromString("Sword-12");
	TechRank = 2;
	AIEngagementRange = 360.f;
	AIAccuracy = 0.96f;
}

void ASolarisSword::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
