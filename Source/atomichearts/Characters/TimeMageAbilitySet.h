// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayEffect.h"
#include "EClassType.h"
#include "TimeMageAbilitySet.generated.h"

class AActor;
class UCurveFloat;

/**
 * Effect applied to frozen enemies
 */
UCLASS(BlueprintType)
class ATOMICHEARTS_API UTimeFreezeEffect : public UGameplayEffect
{
	GENERATED_BODY()
public:
	UTimeFreezeEffect();
};

/**
 * Effect applied to slowed enemies  
 */
UCLASS(BlueprintType)
class ATOMICHEARTS_API UTimeSlowEffect : public UGameplayEffect
{
	GENERATED_BODY()
public:
	UTimeSlowEffect();
};

/**
 * Effect for Phase Shift intangibility
 */
UCLASS(BlueprintType)
class ATOMICHEARTS_API UPhaseShiftEffect : public UGameplayEffect
{
	GENERATED_BODY()
public:
	UPhaseShiftEffect();
};

/**
 * Chrono Trap - A placed trap that warps time when triggered
 */
UCLASS(BlueprintType, HideDropdown)
class ATOMICHEARTS_API AChronoTrap : public AActor
{
	GENERATED_BODY()
	
public:
	AChronoTrap();

	void Initialize(float Duration, float Radius, float SlowPercent, AActor* Owner);

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnTrapTriggered();

	UPROPERTY()
	float TrapDuration = 10.f;

	UPROPERTY()
	float EffectRadius = 300.f;

	UPROPERTY()
	float SlowPercent = 0.5f;

	UPROPERTY()
	AActor* TrapOwner = nullptr;

	FTimerHandle LifetimeHandle;
};

/**
 * Time Mage specific ability implementations - Crowd Control specialist
 * Time Stop: Freeze all enemies in area for 4 seconds
 * Time Slow: Reduce enemy speed by 50%
 * Chrono Trap: Place trap that warps time
 * Phase Shift: Become intangible
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ATOMICHEARTS_API UTimeMageAbilitySet : public UActorComponent
{
	GENERATED_BODY()

public:
	UTimeMageAbilitySet();

	/** Time Stop - Ultimate: Freeze all enemies in radius for 4 seconds */
	UFUNCTION(BlueprintCallable)
	void ExecuteTimeStop(float Radius = 500.f, float Duration = 4.f);

	/** Time Slow - Slow enemies in area by percent for duration */
	UFUNCTION(BlueprintCallable)
	void ExecuteTimeSlow(float Radius = 400.f, float SlowPercent = 0.5f, float Duration = 6.f);

	/** Chrono Trap - Place trap that applies time slow when enemies enter */
	UFUNCTION(BlueprintCallable)
	AChronoTrap* PlaceChronoTrap(float Radius = 300.f, float SlowPercent = 0.5f, float Duration = 10.f);

	/** Phase Shift - Make owner intangible for duration */
	UFUNCTION(BlueprintCallable)
	void ExecutePhaseShift(float Duration = 3.f);

	/** Check if currently intangible */
	UFUNCTION(BlueprintPure)
	bool IsPhaseShifted() const { return bIsPhaseShifted; }

protected:
	virtual void BeginPlay() override;

private:
	void ApplyTimeFreezeToEnemiesInRadius(AActor* Owner, float Radius, float Duration);
	void ApplyTimeSlowToEnemiesInRadius(AActor* Owner, float Radius, float SlowPercent, float Duration);
	TArray<AActor*> GetEnemiesInRadius(AActor* Owner, float Radius);
	
	UPROPERTY()
	bool bIsPhaseShifted = false;

	UPROPERTY()
	float PhaseShiftEndTime = 0.f;

	// Config
	UPROPERTY(EditAnywhere, Category = "Time Mage|Config")
	float TimeStopRadius = 500.f;

	UPROPERTY(EditAnywhere, Category = "Time Mage|Config")
	float TimeStopDuration = 4.f;

	UPROPERTY(EditAnywhere, Category = "Time Mage|Config")
	float TimeSlowRadius = 400.f;

	UPROPERTY(EditAnywhere, Category = "Time Mage|Config")
	float TimeSlowPercent = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Time Mage|Config")
	float TimeSlowDuration = 6.f;

	UPROPERTY(EditAnywhere, Category = "Time Mage|Config")
	float ChronoTrapRadius = 300.f;

	UPROPERTY(EditAnywhere, Category = "Time Mage|Config")
	float ChronoTrapDuration = 10.f;

	UPROPERTY(EditAnywhere, Category = "Time Mage|Config")
	float PhaseShiftDuration = 3.f;
};
