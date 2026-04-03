// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/AChromeScout7.h"

AChromeScout7::AChromeScout7()
{
	WeaponName = FText::FromString("Chrome Scout-7 \"Eagle Eye\"");
	WeaponDescription = FText::FromString("Long-range scout rifle. Sees targets before they see you.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 65.f;
	Stats.FireRate = 0.7f;
	Stats.Range = 12000.f;
	Stats.Accuracy = 0.97f;
	Stats.HeadshotMultiplier = 3.0f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 18000.f;

	MagazineSize = 6;
	MaxReserveAmmo = 24;
	FireRate = 0.7f;

	ZoomedFOV = 18.f;
	ScopeZoomFOV = 18.f;

	NeonColor = FLinearColor(0.4f, 0.5f, 0.85f, 1.0f);
	Manufacturer = FText::FromString("Chrome Corporation");
	ModelDesignation = FText::FromString("Scout-7");
	TechRank = 2;
	AIEngagementRange = 9000.f;
	AIAccuracy = 0.94f;
}

void AChromeScout7::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
