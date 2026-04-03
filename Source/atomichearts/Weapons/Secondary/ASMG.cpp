// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/ASMG.h"

ASMG::ASMG()
{
	WeaponName = FText::FromString("Ghost SMG-2");
	WeaponDescription = FText::FromString("Compact sub-machine gun. High fire rate, low recoil. Perfect for close encounters.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 14.f;
	Stats.FireRate = 0.05f;
	Stats.Range = 2000.f;
	Stats.Accuracy = 0.65f;
	Stats.HeadshotMultiplier = 1.8f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 3500.f;

	MagazineSize = 30;
	MaxReserveAmmo = 150;
	FireRate = 0.05f;

	NeonColor = FLinearColor(0.5f, 0.0f, 1.0f, 1.0f);
	Manufacturer = FText::FromString("Ghost Dynamics");
	ModelDesignation = FText::FromString("SMG-2");
	TechRank = 0;
	AIEngagementRange = 1500.f;
	AIAccuracy = 0.60f;
}

void ASMG::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
