// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/NeonSawedOff3.h"

ANeonSawedOff3::ANeonSawedOff3()
{
	WeaponName = FText::FromString("Neon Sawed-Off-3 Street");
	WeaponDescription = FText::FromString("Cut-down street shotgun. Maximum carnage at point-blank range.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 22.f;
	Stats.FireRate = 0.9f;
	Stats.Range = 500.f;
	Stats.Accuracy = 0.35f;
	Stats.HeadshotMultiplier = 1.4f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 1000.f;

	MagazineSize = 2;
	MaxReserveAmmo = 16;
	FireRate = 0.9f;

	PelletCount = 6;
	SpreadAngle = 25.f;

	NeonColor = FLinearColor(1.0f, 0.1f, 0.3f, 1.0f);
	Manufacturer = FText::FromString("Neon Arms");
	ModelDesignation = FText::FromString("Sawed-Off-3");
	TechRank = 0;
	AIEngagementRange = 500.f;
	AIAccuracy = 0.50.f;
}

void ANeonSawedOff3::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
