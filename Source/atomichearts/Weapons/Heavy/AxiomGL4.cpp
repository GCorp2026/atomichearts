// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/AxiomGL4.h"

CAxiomGL4::CAxiomGL4()
{
	WeaponName = FText::FromString("Axiom GL-4 \"Grenade Launcher\"");
	WeaponDescription = FText::FromString("40mm grenade launcher. Fires high-explosive rounds that detonate on contact.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Explosive;

	Stats.Damage = 110.f;
	Stats.FireRate = 0.8f;
	Stats.Range = 3500.f;
	Stats.Accuracy = 0.82f;
	Stats.HeadshotMultiplier = 1.0f;
	Stats.LegshotMultiplier = 1.0f;
	Stats.MaxRange = 5000.f;

	MagazineSize = 4;
	MaxReserveAmmo = 12;
	FireRate = 0.8f;

	ExplosionRadius = 400.f;
	ProjectileSpeed = 1500.f;

	NeonColor = FLinearColor(0.7f, 0.5f, 0.0f, 1.0f);
	Manufacturer = FText::FromString("Axiom Industries");
	ModelDesignation = FText::FromString("GL-4");
	TechRank = 1;
	AIEngagementRange = 3000.f;
	AIAccuracy = 0.78f;
}

void CAxiomGL4::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
