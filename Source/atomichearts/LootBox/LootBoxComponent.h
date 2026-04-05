#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LootBoxData.h"
#include "LootBoxComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLootBoxOpened, const FLootBoxResult&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSilverChanged, int32, NewBalance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLootBoxReady);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATOMICHEARTS_API ULootBoxComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULootBoxComponent();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Loot Box")
	void OpenLootBox(ELootBoxType Type);

	UFUNCTION(BlueprintCallable, Category = "Loot Box")
	void SkipAnimation();

	UFUNCTION(BlueprintCallable, Category = "Loot Box")
	int32 GetDeluxeCounter() const { return DeluxeCounter; }

	UFUNCTION(BlueprintCallable, Category = "Loot Box")
	bool ShouldGrantPremier() const { return DeluxeCounter >= 10; }

	UFUNCTION(BlueprintCallable, Category = "Loot Box|Stats")
	int32 GetSilverBalance() const { return SilverBalance; }

	UFUNCTION(BlueprintCallable, Category = "Loot Box|Stats")
	bool HasEnoughSilver(ELootBoxType Type) const;

	UFUNCTION(BlueprintCallable, Category = "Loot Box|Stats")
	int32 GetTotalShards() const { return TotalShards; }

	UFUNCTION(BlueprintCallable, Category = "Loot Box")
	void AddDailyLoginReward();

	UFUNCTION(BlueprintCallable, Category = "Loot Box")
	void AddStrikeReward();

	UFUNCTION(BlueprintCallable, Category = "Loot Box")
	void AddCrucibleWinReward();

	UFUNCTION(BlueprintCallable, Category = "Loot Box")
	void AddRaidCompletionReward();

	UFUNCTION(BlueprintCallable, Category = "Loot Box")
	void AddSilver(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Loot Box")
	bool SpendSilver(int32 Amount);

public:
	UPROPERTY(BlueprintAssignable, Category = "Loot Box")
	FOnLootBoxOpened OnLootBoxOpened;

	UPROPERTY(BlueprintAssignable, Category = "Loot Box")
	FOnSilverChanged OnSilverChanged;

	UPROPERTY(BlueprintAssignable, Category = "Loot Box")
	FOnLootBoxReady OnLootBoxReady;

protected:
	UFUNCTION(Server, Reliable)
	void ServerOpenLootBox(ELootBoxType Type);

	UFUNCTION(Server, Reliable)
	void ServerSpendSilver(int32 Amount);

	FLootBoxResult GenerateLootBoxResult(ELootBoxType Type);

	EWeaponRarity RollRarity(ELootBoxType Type);

	FLootBoxReward GenerateItem(ELootBoxType Type, EWeaponRarity Rarity);

	bool CheckIsDuplicate(const FString& ItemId);

	void ConvertDuplicateToShards(const FLootBoxReward& Item);

	void GrantDust(int32 Amount);

private:
	UPROPERTY(Replicated)
	int32 SilverBalance = 500; // Starting silver

	UPROPERTY(Replicated)
	int32 TotalShards = 0;

	UPROPERTY(Replicated)
	int32 DustCurrency = 0;

	UPROPERTY(Replicated)
	int32 DeluxeCounter = 0;

	UPROPERTY(Replicated)
	TArray<FString> OwnedItemIds;

	UPROPERTY(Replicated)
	bool bIsOpening = false;

	UPROPERTY()
	FLootBoxResult PendingResult;

	// Rarity chances
	const TMap<EWeaponRarity, float> StandardRarityChances = {
		{EWeaponRarity::Common, 0.60f},
		{EWeaponRarity::Uncommon, 0.30f},
		{EWeaponRarity::Rare, 0.08f},
		{EWeaponRarity::Legendary, 0.02f},
		{EWeaponRarity::Exotic, 0.00f}
	};

	const TMap<EWeaponRarity, float> DeluxeRarityChances = {
		{EWeaponRarity::Common, 0.00f},
		{EWeaponRarity::Uncommon, 0.40f},
		{EWeaponRarity::Rare, 0.40f},
		{EWeaponRarity::Legendary, 0.18f},
		{EWeaponRarity::Exotic, 0.02f}
	};

	const TMap<EWeaponRarity, float> PremierRarityChances = {
		{EWeaponRarity::Common, 0.00f},
		{EWeaponRarity::Uncommon, 0.00f},
		{EWeaponRarity::Rare, 0.00f},
		{EWeaponRarity::Legendary, 0.50f},
		{EWeaponRarity::Exotic, 0.50f}
	};
};
