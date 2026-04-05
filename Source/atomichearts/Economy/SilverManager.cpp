#include "SilverManager.h"

void USilverManager::BeginPlay()
{
	Super::BeginPlay();
	SetIsReplicated(true);
}

USilverManager::USilverManager()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(true);
}

void USilverManager::AwardSilver(int32 Amount, const FString& Source)
{
	if (GetOwner()->HasAuthority())
	{
		CurrentBalance += Amount;
		TotalEarned += Amount;

		OnBalanceChanged.Broadcast(CurrentBalance);
		OnTransaction.Broadcast(Amount, Source);

		UE_LOG(LogTemp, Log, TEXT("Silver awarded: +%d from %s. New balance: %d"),
			Amount, *Source, CurrentBalance);
	}
}

bool USilverManager::SpendSilver(int32 Amount)
{
	if (CurrentBalance < Amount) return false;

	if (GetOwner()->HasAuthority())
	{
		CurrentBalance -= Amount;
		TotalSpent += Amount;

		OnBalanceChanged.Broadcast(CurrentBalance);
		OnTransaction.Broadcast(-Amount, TEXT("Purchase"));

		UE_LOG(LogTemp, Log, TEXT("Silver spent: -%d. New balance: %d"),
			Amount, CurrentBalance);

		return true;
	}

	return false;
}

void USilverManager::SetBalance(int32 NewBalance)
{
	if (GetOwner()->HasAuthority())
	{
		CurrentBalance = NewBalance;
		OnBalanceChanged.Broadcast(CurrentBalance);
	}
}
