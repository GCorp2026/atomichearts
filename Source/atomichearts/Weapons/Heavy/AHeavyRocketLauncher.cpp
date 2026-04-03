// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/AHeavyRocketLauncher.h"

AHeavyRocketLauncher::AHeavyRocketLauncher()
{
	WeaponName = FText::FromString("Axiom RL-9 \"Hellfire\"");
	WeaponDescription = FText::FromString("Incendiary rocket launcher. Rockets explode on impact and ignite the target.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Explosive;

	Stats.Damage = 130.f;
	Stats.FireRate = 1.2f;
	Stats.Range = 7000.f;
	Stats.Accuracy = 0.88f;
	Stats.HeadshotMultiplier = 1.0f;
	Stats.LegshotMultiplier = 1.0f;
	Stats.MaxRange = 9000.f;

	MagazineSize = 3;
	MaxReserveAmmo = 9;
	FireRate = 1.2f;

	ExplosionRadius = 450.f;
	BurnDamage = 30.f;
	BurnDuration = 3.f;
	RocketSpeed = 2200.f;

	NeonColor = FLinearColor(1.0f, 0.4f, 0.0f, 1.0f);
	Manufacturer = FText::FromString("Axiom Industries");
	ModelDesignation = FText::FromString("RL-9");
	TechRank = 1;
	AIEngagementRange = 4500.f;
	AIAccuracy = 0.75f;
}

void AHeavyRocketLauncher::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
