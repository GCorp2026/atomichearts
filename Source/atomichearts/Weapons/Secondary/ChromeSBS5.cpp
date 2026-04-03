// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/ChromeSBS5.h"

AChromeSBS5::AChromeSBS5()
{
	WeaponName = FText::FromString("Chrome SBS-5 Breacher");
	WeaponDescription = FText::FromString("Short-barrel breacher shotgun. Military room-clearing specialist.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 20.f;
	Stats.FireRate = 0.75f;
	Stats.Range = 600.f;
	Stats.Accuracy = 0.42f;
	Stats.HeadshotMultiplier = 1.5f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 1200.f;

	MagazineSize = 4;
	MaxReserveAmmo = 24;
	FireRate = 0.75f;

	PelletCount = 8;
	SpreadAngle = 20.f;

	NeonColor = FLinearColor(0.5f, 0.5f, 0.6f, 1.0f);
	Manufacturer = FText::FromString("Chrome Military");
	ModelDesignation = FText::FromString("SBS-5");
	TechRank = 1;
	AIEngagementRange = 600.f;
	AIAccuracy = 0.52.f;
}

void AChromeSBS5::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
