// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "EArmorSlot.h"
#include "EClassType.h"
#include "UObject/NoExportTypes.h"
#include "ExoticArmorNameGenerator.generated.h"

/**
 * Procedural exotic armor name generator
 * Combines prefixes, base names, and nicknames for unique armor names
 */
UCLASS(BlueprintType)
class ATOMICHEARTS_API UExoticArmorNameGenerator : public UObject {
    GENERATED_BODY()

public:
    UExoticArmorNameGenerator();

    /**
     * Generate an exotic armor name based on class, slot, and seed
     */
    UFUNCTION(BlueprintCallable, Category = "Armor|Name")
    static FString GenerateName(EClassType ClassType, EArmorSlot Slot, int32 Seed);

    /**
     * Generate a random exotic armor name
     */
    UFUNCTION(BlueprintCallable, Category = "Armor|Name")
    static FString GenerateRandomName(EClassType ClassType, EArmorSlot Slot);

    /**
     * Get slot-specific suffix for names
     */
    UFUNCTION(BlueprintCallable, Category = "Armor|Name")
    static FString GetSlotSuffix(EArmorSlot Slot);

    /**
     * Get class-specific name prefix
     */
    UFUNCTION(BlueprintCallable, Category = "Armor|Name")
    static FString GetClassPrefix(EClassType ClassType);

private:
    // Name generation data
    static const TMap<EClassType, TArray<FString>>& GetClassPrefixes();
    static const TMap<EArmorSlot, TArray<FString>>& GetSlotBaseNames();
    static const TArray<FString>& GetNicknames();

    // Helper for seeded random selection
    static int32 GetSeededRandom(int32 Seed, int32 ArraySize);
};
