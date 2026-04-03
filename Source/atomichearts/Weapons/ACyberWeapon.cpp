// Copyright 2026 Atomic Hearts Team

#include "Weapons/ACyberWeapon.h"
#include "Components/SkeletalMeshComponent.h"

ACyberWeapon::ACyberWeapon()
{
	AmmoType = EAmmoType::EAT_Energy;

	if (bHasNeonGlow)
	{
		ApplyNeonGlow();
	}
}

void ACyberWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (bHasNeonGlow)
	{
		ApplyNeonGlow();
	}
}

void ACyberWeapon::ApplyNeonGlow()
{
	if (!WeaponMesh) return;

	TArray<UMaterialInterface*> Materials = WeaponMesh->GetMaterials();
	for (int32 i = 0; i < Materials.Num(); ++i)
	{
		if (UMaterialInstanceDynamic* DynMat = WeaponMesh->CreateDynamicMaterialInstance(i))
		{
			DynMat->SetVectorParameterValue(FName("NeonColor"), NeonColor);
			DynMat->SetScalarParameterValue(FName("NeonIntensity"), 2.0f);
			DynMat->SetScalarParameterValue(FName("EmissiveGlow"), 1.0f);
		}
	}
}

void ACyberWeapon::RemoveNeonGlow()
{
	if (!WeaponMesh) return;

	TArray<UMaterialInterface*> Materials = WeaponMesh->GetMaterials();
	for (int32 i = 0; i < Materials.Num(); ++i)
	{
		if (UMaterialInstanceDynamic* DynMat = WeaponMesh->CreateDynamicMaterialInstance(i))
		{
			DynMat->SetScalarParameterValue(FName("EmissiveGlow"), 0.0f);
		}
	}
}
