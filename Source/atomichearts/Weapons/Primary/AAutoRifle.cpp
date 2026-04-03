// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/AAutoRifle.h"

AAutoRifle::AAutoRifle()
{
	WeaponName = FText::FromString("Axiom AR-7");
	WeaponDescription = FText::FromString("Fully automatic assault rifle. Reliable in close-to-mid range combat.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 22.f;
	Stats.FireRate = 0.08f;
	Stats.Range = 4500.f;
	Stats.Accuracy = 0.78f;
	Stats.HeadshotMultiplier = 2.0f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 8000.f;

	MagazineSize = 35;
	MaxReserveAmmo = 140;
	FireRate = 0.08f;

	NeonColor = FLinearColor(0.0f, 0.9f, 0.3f, 1.0f);
	Manufacturer = FText::FromString("Axiom Industries");
	ModelDesignation = FText::FromString("AR-7");
	TechRank = 1;
	AIEngagementRange = 3500.f;
	AIAccuracy = 0.75f;
}

void AAutoRifle::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
