// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/CChromeRocketLauncher.h"

CChromeRocketLauncher::CChromeRocketLauncher()
{
	WeaponName = FText::FromString("Chrome RL-7 \"Crusader\"");
	WeaponDescription = FText::FromString("Chrome Corps holy rocket launcher. Sanctified warheads track corrupted entities.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Explosive;

	Stats.Damage = 145.f;
	Stats.FireRate = 1.3f;
	Stats.Range = 7500.f;
	Stats.Accuracy = 0.90f;
	Stats.HeadshotMultiplier = 1.0f;
	Stats.LegshotMultiplier = 1.0f;
	Stats.MaxRange = 9500.f;

	MagazineSize = 3;
	MaxReserveAmmo = 9;
	FireRate = 1.3f;

	ExplosionRadius = 480.f;
	RocketSpeed = 2400.f;
	bHomingRocket = true;

	NeonColor = FLinearColor(0.2f, 0.6f, 1.0f, 1.0f);
	EnergyColor = FLinearColor(0.4f, 0.8f, 1.0f, 1.0f);
	Manufacturer = FText::FromString("Chrome Corporation");
	ModelDesignation = FText::FromString("RL-7");
	TechRank = 2;
	AIEngagementRange = 5000.f;
	AIAccuracy = 0.88f;
}

void CChromeRocketLauncher::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
