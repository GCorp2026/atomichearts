// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/GhostHC3.h"

AGhostHC3::AGhostHC3()
{
	WeaponName = FText::FromString("Ghost HC-3 Silent");
	WeaponDescription = FText::FromString("Whisper-quiet heavy pistol. Near-silent elimination tool.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 38.f;
	Stats.FireRate = 0.35f;
	Stats.Range = 2000.f;
	Stats.Accuracy = 0.76f;
	Stats.HeadshotMultiplier = 2.3f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 3500.f;

	MagazineSize = 8;
	MaxReserveAmmo = 40;
	FireRate = 0.35f;

	NeonColor = FLinearColor(0.4f, 0.0f, 0.6f, 1.0f);
	Manufacturer = FText::FromString("Ghost Dynamics");
	ModelDesignation = FText::FromString("HC-3");
	TechRank = 2;
	AIEngagementRange = 1400.f;
	AIAccuracy = 0.70.f;
}

void AGhostHC3::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
