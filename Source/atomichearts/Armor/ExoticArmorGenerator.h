// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "EArmorSlot.h"
#include "EClassType.h"
#include "ExoticArmorData.h"
#include "UObject/NoExportTypes.h"
#include "ExoticArmorGenerator.generated.h"

/**
 * Main generator for procedural exotic armor pieces
 * Creates 50 unique exotic armors (5 slots × 10 per class)
 */
UCLASS(BlueprintType)
class ATOMICHEARTS_API UExoticArmorGenerator : public UObject {
    GENERATED_BODY()

public:
    UExoticArmorGenerator();

    /**
     * Generate exotic armor by index (0-9) for given slot and class
     */
    UFUNCTION(BlueprintCallable, Category = "Armor|Exotic")
    FGeneratedExoticArmor GenerateExotic(int32 ExoticIndex, EArmorSlot Slot, EClassType ClassType);

    /**
     * Generate random exotic armor for given slot and class
     */
    UFUNCTION(BlueprintCallable, Category = "Armor|Exotic")
    FGeneratedExoticArmor GenerateRandomExotic(EArmorSlot Slot, EClassType ClassType);

    /**
     * Get intrinsic for class at index
     */
    UFUNCTION(BlueprintCallable, Category = "Armor|Exotic")
    EExoticIntrinsic GetIntrinsicForIndex(int32 Index, EClassType ClassType);

    /**
     * Generate lore entry for exotic
     */
    UFUNCTION(BlueprintCallable, Category = "Armor|Exotic")
    FString GenerateLore(EClassType ClassType, int32 ExoticIndex, EArmorSlot Slot);

    /**
     * Generate blockchain ID for exotic
     */
    UFUNCTION(BlueprintCallable, Category = "Armor|Exotic")
    FGuid GenerateBlockchainID(EClassType ClassType, EArmorSlot Slot, int32 ExoticIndex);

    /**
     * Get unique ID string for exotic
     */
    UFUNCTION(BlueprintCallable, Category = "Armor|Exotic")
    FString GetUniqueIDString(EClassType ClassType, EArmorSlot Slot, int32 ExoticIndex);

protected:
    // Generate stats based on class
    FArmorStats GenerateStats(EClassType ClassType, int32 ExoticIndex, int32 Seed);

    // Generate visual properties
    FLinearColor GenerateNeonColor(EClassType ClassType, EExoticIntrinsic Intrinsic);
    int32 GenerateModelVariant(int32 Seed);

    // Lore templates by class
    static const TMap<EClassType, TArray<FString>>& GetLoreByClass();

private:
    // Helper functions
    static FString GetClassPrefix(EClassType ClassType);
    static FString GetSlotPrefix(EArmorSlot Slot);
    static FRandomStream GetSeededStream(int32 Seed);
};
