// Copyright 2026 Atomic Hearts Team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "EBoxType.h"
#include "ULootBoxManager.generated.h"

UCLASS()
class ATOMICHEARTS_API ULootBoxManager : public UObject
{
	GENERATED_BODY()

public:
	ULootBoxManager();

	UFUNCTION(BlueprintCallable, Category = "Loot")
	FLootBoxResult OpenBox(EBoxType BoxType, int64 PlayerID);

	UFUNCTION(BlueprintCallable, Category = "Loot")
	void AddPurchaseCounter(EBoxType BoxType);

	UFUNCTION(BlueprintCallable, Category = "Loot")
	bool IsPremierUnlocked() const;

	UFUNCTION(BlueprintCallable, Category = "Loot")
	void ResetCounter();

	UFUNCTION(BlueprintCallable, Category = "Loot")
	int32 GetCounter() const { return BoxesPurchasedCounter; }

	UFUNCTION(BlueprintCallable, Category = "Loot")
	int32 GetStartingSilver() const { return StartingSilver; }

	UFUNCTION(BlueprintCallable, Category = "Loot")
	int32 GetBoxCost(EBoxType BoxType) const;

	UFUNCTION(BlueprintCallable, Category = "Loot")
	void SetPlayerSilver(int64 PlayerID, int32 Silver);

	UFUNCTION(BlueprintCallable, Category = "Loot")
	int32 GetPlayerSilver(int64 PlayerID) const;

protected:
	FGeneratedItem RollItem(EBoxType BoxType, bool bIsClassSpecific = false);
	EWeaponRarity RollRarity(EBoxType BoxType) const;
	FGeneratedItem GenerateWeapon(EWeaponRarity Rarity, bool bClassSpecific);
	FGeneratedItem GenerateArmor(EWeaponRarity Rarity);

	UPROPERTY()
	int32 BoxesPurchasedCounter = 0;

	UPROPERTY()
	int32 StartingSilver = 500;

	UPROPERTY()
	TMap<int64, int32> PlayerSilverMap;

	static constexpr int32 PREMIER_UNLOCK_THRESHOLD = 10;
	static constexpr int32 STANDARD_COST = 100;
	static constexpr int32 DELUXE_COST = 500;
};
