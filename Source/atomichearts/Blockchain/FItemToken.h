// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FItemToken.generated.h"

/**
 * Represents a blockchain-registered item token
 */
USTRUCT(BlueprintType)
struct FItemToken
{
    GENERATED_BODY()

    /** Unique hash: sha256(seed + slot + timestamp) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Blockchain|Item")
    FString TokenID;

    /** Account/wallet ID of current owner */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Blockchain|Item")
    FString OwnerID;

    /** Item category: "weapon" or "armor" */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Blockchain|Item")
    FString ItemType;

    /** Specific class: "Primary_AR", "Helmet", etc */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Blockchain|Item")
    FString ItemClass;

    /** Generation seed for procedural properties */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Blockchain|Item")
    int32 Seed;

    /** Full item display name */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Blockchain|Item")
    FString Name;

    /** Rarity tier: Common, Uncommon, Rare, Legendary, Exotic */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Blockchain|Item")
    FString Rarity;

    /** Unix timestamp when token was created */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Blockchain|Item")
    int64 CreatedAt;

    /** Unix timestamp of last trade */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Blockchain|Item")
    int64 LastTradedAt;

    /** Last sale price in silver */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Blockchain|Item")
    int32 LastPrice;
};
