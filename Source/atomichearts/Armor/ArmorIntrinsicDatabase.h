// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "ExoticArmorData.h"
#include "UObject/NoExportTypes.h"
#include "ArmorIntrinsicDatabase.generated.h"

/**
 * Database for exotic armor intrinsic abilities
 * Provides DataTable access and procedural intrinsic effects
 */
UCLASS(BlueprintType)
class ATOMICHEARTS_API UArmorIntrinsicDatabase : public UObject {
    GENERATED_BODY()

public:
    UArmorIntrinsicDatabase();

    /**
     * Get intrinsic definition by type
     */
    UFUNCTION(BlueprintCallable, Category = "Armor|Intrinsic")
    FExoticIntrinsicDefinition GetIntrinsicDefinition(EExoticIntrinsic Intrinsic) const;

    /**
     * Get all intrinsics for a specific class
     */
    UFUNCTION(BlueprintCallable, Category = "Armor|Intrinsic")
    TArray<EExoticIntrinsic> GetIntrinsicsForClass(EClassType ClassType) const;

    /**
     * Get intrinsic description
     */
    UFUNCTION(BlueprintCallable, Category = "Armor|Intrinsic")
    static FString GetIntrinsicDescription(EExoticIntrinsic Intrinsic);

    /**
     * Get intrinsic display name
     */
    UFUNCTION(BlueprintCallable, Category = "Armor|Intrinsic")
    static FString GetIntrinsicDisplayName(EExoticIntrinsic Intrinsic);

    /**
     * Get intrinsic effect color
     */
    UFUNCTION(BlueprintCallable, Category = "Armor|Intrinsic")
    static FLinearColor GetIntrinsicColor(EExoticIntrinsic Intrinsic);

    /**
     * Calculate intrinsic effect magnitude based on class and index
     */
    UFUNCTION(BlueprintCallable, Category = "Armor|Intrinsic")
    static float CalculateEffectMagnitude(EExoticIntrinsic Intrinsic, EClassType ClassType);

protected:
    // Initialize the intrinsic database
    void InitializeIntrinsics();

private:
    // Internal lookup maps
    static const TMap<EExoticIntrinsic, FExoticIntrinsicDefinition>& GetIntrinsicMap();
};
