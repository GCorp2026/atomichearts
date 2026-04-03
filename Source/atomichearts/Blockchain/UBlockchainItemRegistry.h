// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FItemToken.h"
#include "UBlockchainItemRegistry.generated.h"

/**
 * Manages blockchain item registration and trading (MVP: local storage)
 */
UCLASS(BlueprintType)
class UBlockchainItemRegistry : public UObject
{
    GENERATED_BODY()

public:
    /** Generate unique token ID using FNV1a hash of seed + itemtype + slot */
    UFUNCTION(BlueprintCallable, Category="Blockchain|Registry")
    FString GenerateTokenID(int32 Seed, FString ItemType, FString Slot);

    /** Register new item when generated/looted */
    UFUNCTION(BlueprintCallable, Category="Blockchain|Registry")
    FItemToken RegisterItem(int32 Seed, FString ItemType, FString Slot, 
                            FString Name, FString Rarity, int64 OwnerID);

    /** Transfer ownership with 30% commission deduction */
    UFUNCTION(BlueprintCallable, Category="Blockchain|Registry")
    bool TransferItem(FString TokenID, int64 FromOwner, int64 ToOwner, int32 Price);

    /** Get item data by token ID */
    UFUNCTION(BlueprintCallable, Category="Blockchain|Registry")
    FItemToken GetItem(FString TokenID);

    /** Get all items owned by an account */
    UFUNCTION(BlueprintCallable, Category="Blockchain|Registry")
    TArray<FItemToken> GetOwnerItems(int64 OwnerID);

    /** Calculate marketplace commission (30%) */
    UFUNCTION(BlueprintPure, Category="Blockchain|Registry")
    int32 CalculateCommission(int32 SalePrice);

    /** Calculate seller's payout (70%) */
    UFUNCTION(BlueprintPure, Category="Blockchain|Registry")
    int32 CalculateSellerPayout(int32 SalePrice);

protected:
    /** In-memory registry (would be smart contract in production) */
    UPROPERTY()
    TMap<FString, FItemToken> ItemRegistry;

private:
    /** FNV1a hash implementation for token ID generation */
    uint32 FNV1aHash(const FString& Input);
};
