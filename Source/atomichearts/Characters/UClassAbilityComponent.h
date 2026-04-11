// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EClassType.h"
#include "UClassAbilityComponent.generated.h"

class UGameplayAbility;
class UAbilitySystemComponent;
class UAnimMontage;

/**
 * Cooldown entry tracking remaining time
 */
USTRUCT(BlueprintType)
struct FCooldownEntry
{
	GENERATED_BODY()

	float RemainingTime = 0.f;
	float TotalTime = 0.f;

	bool IsReady() const { return RemainingTime <= 0.f; }
	float GetProgress() const { return TotalTime > 0.f ? 1.f - (RemainingTime / TotalTime) : 1.f; }
};

/**
 * Ability definition for a slot
 */
USTRUCT(BlueprintType)
struct FAbilityDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAbilityType AbilityType = EAbilityType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cost = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> AbilityClass;
};

/**
 * GAS ability class mapping
 */
USTRUCT(BlueprintType)
struct FAbilityClassMapping
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	EAbilityType AbilityType = EAbilityType::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TSubclassOf<UGameplayAbility> AbilityClass;
};

/**
 * Component managing all class abilities, cooldowns, and ultimates
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ATOMICHEARTS_API UClassAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UClassAbilityComponent();

	/** Set the character's class type and configure abilities */
	UFUNCTION(BlueprintCallable)
	void SetClass(EClassType NewClass);

	/** Get current class */
	UFUNCTION(BlueprintPure)
	EClassType GetClass() const { return CurrentClass; }

	/** Try to activate ability in given slot */
	UFUNCTION(BlueprintCallable)
	bool ActivateAbility(int32 SlotIndex);

	/** Activate ultimate ability */
	UFUNCTION(BlueprintCallable)
	bool ActivateUltimate();

	/** Check if ability slot is on cooldown */
	UFUNCTION(BlueprintPure)
	bool IsAbilityReady(int32 SlotIndex) const;

	/** Get cooldown progress 0-1 */
	UFUNCTION(BlueprintPure)
	float GetCooldownProgress(int32 SlotIndex) const;

	/** Reduce cooldowns (e.g. from haste) */
	UFUNCTION(BlueprintCallable)
	void ReduceCooldowns(float Amount);

	/** Get ability type for slot */
	UFUNCTION(BlueprintPure)
	EAbilityType GetAbilityType(int32 SlotIndex) const;

	/** Get GAS ability class for ability type */
	TSubclassOf<UGameplayAbility> GetAbilityClassForType(EAbilityType AbilityType) const;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void ConfigureAbilitiesForClass();
	void StartCooldown(int32 SlotIndex, float Duration);
	void GrantAbilitiesToActor();

	UPROPERTY()
	EClassType CurrentClass = EClassType::TechMage;

	UPROPERTY()
	TArray<FAbilityDefinition> AbilitySlots;

	UPROPERTY()
	TArray<FCooldownEntry> Cooldowns;

	UPROPERTY()
	TMap<int32, float> UltimateChargePercent;

	UPROPERTY()
	AActor* OwnerActor = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TArray<FAbilityClassMapping> GASAbilityClasses;

	UPROPERTY()
	UAbilitySystemComponent* CachedAbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UGameplayAbility> TimeSlowAbilityClass;

	float ChargeAccumulator = 0.f;
};
