// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "EArmorSlot.h"
#include "EArmorRarity.h"
#include "EClassType.h"
#include "FArmorStats.h"
#include "EExoticIntrinsic.h"
#include "FExoticArmorResult.h"
#include "UObject/NoExportTypes.h"
#include "UExoticArmorGenerator.generated.h"

UCLASS()
class ATOMICHEARTS_API UExoticArmorGenerator : public UObject
{
    GENERATED_BODY()

public:
    UExoticArmorGenerator();

    UFUNCTION(BlueprintCallable, Category = "Armor|Exotic")
    FExoticArmorResult GenerateExotic(int32 Index, EArmorSlot Slot, EClassType ClassType);

    UFUNCTION(BlueprintCallable, Category = "Armor|Exotic")
    static FString GetIntrinsicName(EExoticIntrinsic Intrinsic);

    UFUNCTION(BlueprintCallable, Category = "Armor|Exotic")
    static FString GenerateLore(EClassType ClassType, int32 ExoticIndex, EArmorSlot Slot);

    UFUNCTION(BlueprintCallable, Category = "Armor|Exotic")
    static FLinearColor GetExoticBorderColor();

private:
    static FRandomStream GetSeededStream(int32 Seed);
    static FString GetExoticName(EClassType ClassType, int32 Index);
    static EExoticIntrinsic GetIntrinsicForClass(EClassType ClassType, int32 Index);
    static TArray<FString> GetExoticPerks(EClassType ClassType, int32 Index);
    static FArmorStats GenerateExoticStats(EClassType ClassType, int32 Index);

    static const TMap<EClassType, TArray<FString>> ExoticNamesByClass;
    static const TMap<EClassType, TArray<EExoticIntrinsic>> IntrinsicsByClass;
    static const TMap<EClassType, TArray<TArray<FString>>> PerksByClass;
};
