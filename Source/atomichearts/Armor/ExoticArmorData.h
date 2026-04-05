// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "EArmorSlot.h"
#include "EArmorRarity.h"
#include "EClassType.h"
#include "EExoticIntrinsic.h"
#include "FArmorStats.h"
#include "ExoticArmorData.generated.h"

/**
 * Data structure for Exotic Armor intrinsic ability definitions
 * Used with DataTable for designer-friendly intrinsic database
 */
USTRUCT(BlueprintType)
struct FExoticIntrinsicDefinition : public FTableRowBase {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString IntrinsicName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EExoticIntrinsic IntrinsicType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EffectMagnitude;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Cooldown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor GlowColor;
};

/**
 * Data structure for Exotic Armor piece definitions
 * Used with DataTable for all 50 exotic armor pieces
 */
USTRUCT(BlueprintType)
struct FExoticArmorDefinition : public FTableRowBase {
    GENERATED_BODY()

    // Identification
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ExoticIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EArmorSlot Slot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EClassType ClassType;

    // Name and lore
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ArmorName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString LoreEntry;

    // Intrinsic
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EExoticIntrinsic Intrinsic;

    // Visual
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor NeonColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ModelVariant;

    // Blockchain
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString BlockchainSymbol;
};

/**
 * Result structure returned by ExoticArmorGenerator
 */
USTRUCT(BlueprintType)
struct FGeneratedExoticArmor {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    int32 ExoticIndex;

    UPROPERTY(BlueprintReadOnly)
    EArmorSlot Slot;

    UPROPERTY(BlueprintReadOnly)
    EClassType ClassType;

    UPROPERTY(BlueprintReadOnly)
    FString Name;

    UPROPERTY(BlueprintReadOnly)
    FString Lore;

    UPROPERTY(BlueprintReadOnly)
    EExoticIntrinsic Intrinsic;

    UPROPERTY(BlueprintReadOnly)
    FString IntrinsicDescription;

    // Stat boosts
    UPROPERTY(BlueprintReadOnly)
    float Mobility;
    
    UPROPERTY(BlueprintReadOnly)
    float Resilience;
    
    UPROPERTY(BlueprintReadOnly)
    float Recovery;
    
    UPROPERTY(BlueprintReadOnly)
    float Discipline;
    
    UPROPERTY(BlueprintReadOnly)
    float Intellect;
    
    UPROPERTY(BlueprintReadOnly)
    float Strength;

    // Visual
    UPROPERTY(BlueprintReadOnly)
    FLinearColor NeonColor;

    UPROPERTY(BlueprintReadOnly)
    int32 ModelVariant;

    // Blockchain
    UPROPERTY(BlueprintReadOnly)
    FGuid BlockchainID;

    // Unique identifier string
    UPROPERTY(BlueprintReadOnly)
    FString UniqueID;

    FGeneratedExoticArmor()
        : ExoticIndex(0)
        , Slot(EArmorSlot::Helmet)
        , ClassType(EClassType::TechMage)
        , Intrinsic(EExoticIntrinsic::None)
        , Mobility(60.f)
        , Resilience(60.f)
        , Recovery(60.f)
        , Discipline(60.f)
        , Intellect(60.f)
        , Strength(60.f)
        , ModelVariant(0)
    {}
};
