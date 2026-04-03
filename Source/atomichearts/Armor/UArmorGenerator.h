#pragma once

#include "CoreMinimal.h"
#include "EArmorSlot.h"
#include "EArmorRarity.h"
#include "FArmorStats.h"
#include "FArmorGeneratorResult.h"
#include "UObject/NoExportTypes.h"
#include "UArmorGenerator.generated.h"

UCLASS()
class ATOMICHEARTS_API UArmorGenerator : public UObject
{
    GENERATED_BODY()

public:
    UArmorGenerator();

    UFUNCTION(BlueprintCallable, Category = "Armor|Generation")
    FArmorGeneratorResult GenerateArmor(int32 Seed, EArmorSlot Slot, EArmorRarity Rarity);

    UFUNCTION(BlueprintCallable, Category = "Armor|Generation")
    FString GenerateArmorName(EArmorSlot Slot, int32 Seed);

    UFUNCTION(BlueprintCallable, Category = "Armor|Generation")
    FArmorStats GenerateStats(EArmorRarity Rarity, int32 Seed);

    UFUNCTION(BlueprintCallable, Category = "Armor|Generation")
    TArray<FString> SelectPerks(EArmorRarity Rarity, int32 Seed);

    UFUNCTION(BlueprintCallable, Category = "Armor|Generation")
    FLinearColor GetBorderColor(EArmorRarity Rarity);

    UFUNCTION(BlueprintCallable, Category = "Armor|Exotic")
    FString GetExoticIntrinsic(EArmorSlot Slot, int32 Seed);

private:
    int32 GetStatMin(EArmorRarity Rarity);
    int32 GetStatMax(EArmorRarity Rarity);
    FRandomStream GetSeededStream(int32 Seed);
    FString GetFaction(int32 Seed);
    FString GetMaterial(const FString& Faction, int32 Seed);
    FString GetSlotSuffix(EArmorSlot Slot, int32 Seed);

    static const TArray<FString> Factions;
    static const TMap<FString, TArray<FString>> MaterialsByFaction;
    static const TMap<EArmorSlot, TArray<FString>> SuffixesBySlot;

    static const TMap<FString, TArray<FString>> ExoticNamesByClass;
};
