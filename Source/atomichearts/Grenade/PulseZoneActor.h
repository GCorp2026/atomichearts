// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PulseZoneActor.generated.h"

class USphereComponent;
class UParticleSystemComponent;

/**
 * Persistent zone that pulses damage/effects at regular intervals.
 */
UCLASS()
class ATOMICHEARTS_API APulseZoneActor : public AActor
{
	GENERATED_BODY()
	
public:
	APulseZoneActor();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Start pulsing */
	void StartPulsing();

	/** Stop pulsing and destroy */
	void StopPulsing();

	/** Set pulse damage */
	void SetPulseDamage(float NewDamage) { PulseDamage = NewDamage; }

	/** Set zone radius */
	void SetZoneRadius(float NewRadius);

	/** Set pulse interval */
	void SetPulseInterval(float NewInterval) { PulseInterval = NewInterval; }

	/** Set zone duration */
	void SetZoneDuration(float NewDuration) { ZoneDuration = NewDuration; }

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** Apply pulse effect to actors inside zone */
	void ApplyPulse();

	/** Destroy zone after duration */
	void DestroyZone();

	/** Damage per pulse */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Pulse Zone", meta = (AllowPrivateAccess = "true"))
	float PulseDamage = 20.f;

	/** Zone radius */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Pulse Zone", meta = (AllowPrivateAccess = "true"))
	float ZoneRadius = 400.f;

	/** Time between pulses (seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Pulse Zone", meta = (AllowPrivateAccess = "true"))
	float PulseInterval = 1.f;

	/** Total lifetime of zone (seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Pulse Zone", meta = (AllowPrivateAccess = "true"))
	float ZoneDuration = 10.f;

	/** Collision sphere representing zone */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* ZoneSphere;

	/** Visual effect */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* PulseParticle;

	/** Timer handle for pulses */
	FTimerHandle PulseTimerHandle;

	/** Timer handle for destruction */
	FTimerHandle DestroyTimerHandle;
};