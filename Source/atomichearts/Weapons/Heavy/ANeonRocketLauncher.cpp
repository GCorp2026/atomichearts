// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/ANeonRocketLauncher.h"

ANeonRocketLauncher::ANeonRocketLauncher()
{
	WeaponName = FText::FromString("Neon RL-3 \"Scrap\"");
	WeaponDescription = FText::FromString("Jury-rigged rocket launcher. No guidance system but devastating payload.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Explosive;

	Stats.Damage = 140.f;
	Stats.FireRate = 1.0f;
	Stats.Range = 5000.f;
	Stats.Accuracy = 0.72f;
	Stats.HeadshotMultiplier = 1.0f;
	Stats.LegshotMultiplier = 1.0f;
	Stats.MaxRange = 7000.f;

	MagazineSize = 2;
	MaxReserveAmmo = 6;
	FireRate = 1.0f;

	ExplosionRadius = 380.f;
	RocketSpeed = 1800.f;
	bHomingRocket = false;

	NeonColor = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f);
	Manufacturer = FText::FromString("Neon Syndicate");
	ModelDesignation = FText::FromString("RL-3");
	TechRank = 0;
	AIEngagementRange = 3500.f;
	AIAccuracy = 0.65f;
}

void ANeonRocketLauncher::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
