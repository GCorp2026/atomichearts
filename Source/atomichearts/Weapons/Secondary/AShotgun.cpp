// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/AShotgun.h"

AShotgun::AShotgun()
{
	WeaponName = FText::FromString("Drift SG-1");
	WeaponDescription = FText::FromString("Pump-action shotgun with wide spread. Clears rooms at close range.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 18.f;        // per pellet
	Stats.FireRate = 0.8f;
	Stats.Range = 800.f;
	Stats.Accuracy = 0.40f;
	Stats.HeadshotMultiplier = 1.5f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 1500.f;

	MagazineSize = 6;
	MaxReserveAmmo = 30;
	FireRate = 0.8f;

	PelletCount = 8;
	SpreadAngle = 15.f;

	NeonColor = FLinearColor(1.0f, 0.5f, 0.0f, 1.0f);
	Manufacturer = FText::FromString("Drift Ordnance");
	ModelDesignation = FText::FromString("SG-1");
	TechRank = 0;
	AIEngagementRange = 800.f;
	AIAccuracy = 0.55f;
}

void AShotgun::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
