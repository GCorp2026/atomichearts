// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/CChromeGL6.h"

CChromeGL6::CChromeGL6()
{
	WeaponName = FText::FromString("Chrome GL-6 \"Breacher\"");
	WeaponDescription = FText::FromString("Tactical breaching grenade launcher. Designed to blow open doors and flush enemies.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Explosive;

	Stats.Damage = 90.f;
	Stats.FireRate = 0.7f;
	Stats.Range = 2000.f;
	Stats.Accuracy = 0.80f;
	Stats.HeadshotMultiplier = 1.0f;
	Stats.LegshotMultiplier = 1.0f;
	Stats.MaxRange = 3000.f;

	MagazineSize = 6;
	MaxReserveAmmo = 18;
	FireRate = 0.7f;

	ExplosionRadius = 300.f;
	ProjectileSpeed = 1200.f;

	NeonColor = FLinearColor(0.2f, 0.4f, 1.0f, 1.0f);
	Manufacturer = FText::FromString("Chrome Corporation");
	ModelDesignation = FText::FromString("GL-6");
	TechRank = 1;
	AIEngagementRange = 2000.f;
	AIAccuracy = 0.75f;
}

void CChromeGL6::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
