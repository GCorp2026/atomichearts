// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SolarBurnZoneActor.generated.h"

class USphereComponent;
class UParticleSystemComponent;

/**
 * Zone that applies burn damage over time to actors inside.
 */
UCLASS()
class ATOMICHEARTS_API ASolarBurnZoneActor : public AActor
{
	GENERATED_BODY()
	
public:
	ASolarBurnZoneActor();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Start burning */
	void StartBurning();

	/** Stop burning and destroy */
	void StopBurning();

	/** Set burn damage per tick */
	void SetBurnDamage(float NewDamage) { BurnDamage = NewDamage; }

	/** Set zone radius */
	void SetZoneRadius(float NewRadius);

	/** Set burn duration */
	void SetBurnDuration(float NewDuration) { BurnDuration = NewDuration; }

	/** Set burn interval */
	void SetBurnInterval(float NewInterval) { BurnInterval = NewInterval; }

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** Apply burn damage to actors inside zone */
	void ApplyBurn();

	/** Destroy zone after duration */
	void DestroyZone();

	/** Damage per burn tick */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Solar Burn", meta = (AllowPrivateAccess = "true"))
	float BurnDamage = 10.f;

	/** Zone radius */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Solar Burn", meta = (AllowPrivateAccess = "true"))
	float ZoneRadius = 400.f;

	/** Time between burn ticks (seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solar Burn", meta = (AllowPrivateAccess = "true"))
	float BurnInterval = 0.5f;

	/** Total lifetime of zone (seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solar Burn", meta = (AllowPrivateAccess = "true"))
	float BurnDuration = 5.f;

	/** Collision sphere representing zone */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* ZoneSphere;

	/** Visual effect */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* BurnParticle;

	/** Timer handle for burn ticks */
	FTimerHandle BurnTimerHandle;

	/** Timer handle for destruction */
	FTimerHandle DestroyTimerHandle;
};