// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EClassType.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "UGrenadeComponent.generated.h"

class AGrenadeProjectile;

/**
 * Grenade component that handles throwing grenades and applying effects.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ATOMICHEARTS_API UGrenadeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGrenadeComponent();

	/** Set the type of grenade to use */
	UFUNCTION(BlueprintCallable)
	void SetGrenadeType(EAbilityType NewType);

	/** Set cooldown duration */
	UFUNCTION(BlueprintCallable)
	void SetCooldown(float NewCooldown);

	/** Throw a grenade from the owner's location and rotation */
	UFUNCTION(BlueprintCallable)
	void ThrowGrenade();

	/** Called when grenade explodes, applies effects */
	UFUNCTION(BlueprintCallable)
	void OnExplode(const FVector& ExplosionLocation);

	/** Get remaining cooldown time */
	UFUNCTION(BlueprintPure)
	float GetCooldownRemaining() const { return CooldownRemaining; }

	/** Check if grenade is ready to throw */
	UFUNCTION(BlueprintPure)
	bool IsReady() const;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	/** Apply effects (damage, area effects) based on grenade type */
	virtual void ApplyEffects(const FVector& ExplosionLocation);

	/** Spawn a projectile actor */
	AGrenadeProjectile* SpawnProjectile(const FVector& Location, const FRotator& Rotation);

	/** Grenade type (Impact, Pulse, Solar, etc.) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade", meta = (AllowPrivateAccess = "true"))
	EAbilityType GrenadeType = EAbilityType::SolarGrenade;

	/** Strength of throw (velocity magnitude) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade", meta = (AllowPrivateAccess = "true"))
	float ThrowStrength = 1500.f;

	/** Base damage dealt by explosion */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade", meta = (AllowPrivateAccess = "true"))
	float Damage = 50.f;

	/** Explosion radius */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade", meta = (AllowPrivateAccess = "true"))
	float Radius = 400.f;

	/** Cooldown between throws */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade", meta = (AllowPrivateAccess = "true"))
	float Cooldown = 3.f;

	/** Current cooldown remaining */
	float CooldownRemaining = 0.f;

	/** Gameplay Ability System cooldown effect class */
	UPROPERTY(EditDefaultsOnly, Category = "Grenade|GAS")
	TSubclassOf<UGameplayEffect> CooldownEffectClass;

	/** Helper to get the owner's Ability System Component */
	UAbilitySystemComponent* GetOwnerAbilitySystemComponent() const;
};