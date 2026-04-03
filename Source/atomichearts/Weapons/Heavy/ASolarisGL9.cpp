// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/ASolarisGL9.h"

ASolarisGL9::ASolarisGL9()
{
	WeaponName = FText::FromString("Solaris GL-9 \"Nova\"");
	WeaponDescription = FText::FromString("Solar grenade launcher. Nova rounds create blinding flashes and devastating area damage.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Explosive;

	Stats.Damage = 120.f;
	Stats.FireRate = 0.9f;
	Stats.Range = 4000.f;
	Stats.Accuracy = 0.88f;
	Stats.HeadshotMultiplier = 1.0f;
	Stats.LegshotMultiplier = 1.0f;
	Stats.MaxRange = 5500.f;

	MagazineSize = 5;
	MaxReserveAmmo = 15;
	FireRate = 0.9f;

	ExplosionRadius = 500.f;
	ProjectileSpeed = 1700.f;

	NeonColor = FLinearColor(1.0f, 0.4f, 0.0f, 1.0f);
	EnergyColor = FLinearColor(1.0f, 0.9f, 0.1f, 1.0f);
	Manufacturer = FText::FromString("Solaris Defense");
	ModelDesignation = FText::FromString("GL-9");
	TechRank = 2;
	AIEngagementRange = 3500.f;
	AIAccuracy = 0.85f;
}

void ASolarisGL9::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
