// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/GhostDetective9.h"

AGhostDetective9::AGhostDetective9()
{
	WeaponName = FText::FromString("Ghost Detective-9 Witness");
	WeaponDescription = FText::FromString("Compact suppressed pistol. Intelligence agents' witness elimination tool.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 22.f;
	Stats.FireRate = 0.15f;
	Stats.Range = 1600.f;
	Stats.Accuracy = 0.80f;
	Stats.HeadshotMultiplier = 2.1f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 2800.f;

	MagazineSize = 10;
	MaxReserveAmmo = 50;
	FireRate = 0.15f;

	NeonColor = FLinearColor(0.2f, 0.0f, 0.5f, 1.0f);
	Manufacturer = FText::FromString("Ghost Dynamics");
	ModelDesignation = FText::FromString("Detective-9");
	TechRank = 2;
	AIEngagementRange = 1000.f;
	AIAccuracy = 0.74.f;
}

void AGhostDetective9::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
