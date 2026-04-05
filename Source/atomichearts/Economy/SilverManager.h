#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SilverManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSilverBalanceChanged, int32, NewBalance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTransaction, int32, Amount, const FString&, Source);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATOMICHEARTS_API USilverManager : public UActorComponent
{
	GENERATED_BODY()

public:
	USilverManager();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Silver Economy")
	void AwardSilver(int32 Amount, const FString& Source);

	UFUNCTION(BlueprintCallable, Category = "Silver Economy")
	bool SpendSilver(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Silver Economy")
	int32 GetBalance() const { return CurrentBalance; }

	UFUNCTION(BlueprintCallable, Category = "Silver Economy")
	void SetBalance(int32 NewBalance);

	UFUNCTION(BlueprintCallable, Category = "Silver Economy")
	bool CanAfford(int32 Amount) const { return CurrentBalance >= Amount; }

public:
	UPROPERTY(BlueprintAssignable, Category = "Silver Economy")
	FOnSilverBalanceChanged OnBalanceChanged;

	UPROPERTY(BlueprintAssignable, Category = "Silver Economy")
	FOnTransaction OnTransaction;

protected:
	UPROPERTY(Replicated)
	int32 CurrentBalance = 500;

	UPROPERTY(Replicated)
	int32 TotalEarned = 0;

	UPROPERTY(Replicated)
	int32 TotalSpent = 0;
};
