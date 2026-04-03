// Copyright 2026 Atomic Hearts Team

#pragma once

#include "CoreMinimal.h"
#include "EWeaponRarity.h"
#include "AtomicheartsWeaponTypes.h"

USTRUCT(BlueprintType)
struct FWeaponPerk
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PerkName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PerkRank = 1; // I–III

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor PerkColor = FLinearColor::White;
};
