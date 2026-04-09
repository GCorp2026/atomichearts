// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGrenadeProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

/**
 * Base grenade projectile that flies through the air and explodes on impact or timer.
 */
UCLASS()
class ATOMICHEARTS_API AGrenadeProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	AGrenadeProjectile();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Called when fuse timer expires (explode in air) */
	void OnFuseExpired();

	/** Trigger explosion */
	void Explode();

	/** Set damage value */
	void SetDamage(float NewDamage) { Damage = NewDamage; }

	/** Set explosion radius */
	void SetExplosionRadius(float NewRadius) { ExplosionRadius = NewRadius; }

	/** Get projectile movement component */
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

protected:
	virtual void BeginPlay() override;

	/** Apply explosion effects (to be overridden by subclasses) */
	virtual void ApplyEffects(const FVector& ExplosionLocation);

	/** Damage dealt by explosion */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade", Replicated)
	float Damage = 50.f;

	/** Explosion radius */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade", Replicated)
	float ExplosionRadius = 400.f;

	/** Fuse time before auto‑explosion (seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade")
	float FuseTime = 3.f;

	/** Collision sphere */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* CollisionSphere;

	/** Movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;

	/** Visual effect (optional placeholder) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* ParticleSystem;
};