// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/GhostSMG6.h"

AGhostSMG6::AGhostSMG6()
{
	WeaponName = FText::FromString("Ghost SMG-6 Invisible");
	WeaponDescription = FText::FromString("Integrated suppressor SMG. Hackers' choice for silent operations.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 16.f;
	Stats.FireRate = 0.06f;
	Stats.Range = 1800.f;
	Stats.Accuracy = 0.68f;
	Stats.HeadshotMultiplier = 1.8f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 3200.f;

	MagazineSize = 25;
	MaxReserveAmmo = 125;
	FireRate = 0.06f;

	NeonColor = FLinearColor(0.3f, 0.0f, 0.8f, 1.0f);
	Manufacturer = FText::FromString("Ghost Dynamics");
	ModelDesignation = FText::FromString("SMG-6");
	TechRank = 2;
	AIEngagementRange = 1200.f;
	AIAccuracy = 0.62.f;
}

void AGhostSMG6::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
