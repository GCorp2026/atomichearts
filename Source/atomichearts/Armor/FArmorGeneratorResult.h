#pragma once

#include "CoreMinimal.h"
#include "EArmorSlot.h"
#include "EArmorRarity.h"
#include "FArmorStats.h"
#include "FArmorGeneratorResult.generated.h"

USTRUCT(BlueprintType)
struct FArmorGeneratorResult
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EArmorSlot Slot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EArmorRarity Rarity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FArmorStats Stats;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Perks;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Intrinsic;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor BorderColor;

    FArmorGeneratorResult()
        : Slot(EArmorSlot::Helmet), Rarity(EArmorRarity::Common), BorderColor(FLinearColor::White) {}
};
