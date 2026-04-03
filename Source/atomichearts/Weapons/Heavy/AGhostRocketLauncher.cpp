// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/AGhostRocketLauncher.h"

AGhostRocketLauncher::AGhostRocketLauncher()
{
	WeaponName = FText::FromString("Ghost RL-5 \"Phantom\"");
	WeaponDescription = FText::FromString("Ghost cell stealth rocket launcher. Whisper-quiet firing with minimal heat signature.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Explosive;

	Stats.Damage = 135.f;
	Stats.FireRate = 1.1f;
	Stats.Range = 6500.f;
	Stats.Accuracy = 0.85f;
	Stats.HeadshotMultiplier = 1.0f;
	Stats.LegshotMultiplier = 1.0f;
	Stats.MaxRange = 8500.f;

	MagazineSize = 3;
	MaxReserveAmmo = 9;
	FireRate = 1.1f;

	ExplosionRadius = 420.f;
	RocketSpeed = 2000.f;
	bHomingRocket = true;

	NeonColor = FLinearColor(0.0f, 1.0f, 0.5f, 1.0f);
	Manufacturer = FText::FromString("Ghost Collective");
	ModelDesignation = FText::FromString("RL-5");
	TechRank = 2;
	AIEngagementRange = 4000.f;
	AIAccuracy = 0.82f;
}

void AGhostRocketLauncher::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
