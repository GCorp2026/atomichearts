// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/CChromeLMG9.h"

CChromeLMG9::CChromeLMG9()
{
	WeaponName = FText::FromString("Chrome LMG-9 \"Duty\"");
	WeaponDescription = FText::FromString("Standard issue Chrome military heavy machine gun. Reliable, deadly, and chrome-plated.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 20.f;
	Stats.FireRate = 0.065f;
	Stats.Range = 5500.f;
	Stats.Accuracy = 0.58f;
	Stats.HeadshotMultiplier = 1.9f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 8500.f;

	MagazineSize = 110;
	MaxReserveAmmo = 220;
	FireRate = 0.065f;

	SuppressionRadius = 550.f;

	NeonColor = FLinearColor(0.3f, 0.5f, 1.0f, 1.0f);
	Manufacturer = FText::FromString("Chrome Corporation");
	ModelDesignation = FText::FromString("LMG-9");
	TechRank = 1;
	AIEngagementRange = 4000.f;
	AIAccuracy = 0.52f;
}

void CChromeLMG9::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
