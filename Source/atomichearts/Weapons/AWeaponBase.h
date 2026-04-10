// Copyright 2026 Atomic Hearts Team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AtomicheartsWeaponTypes.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "AWeaponBase.generated.h"

class USoundCue;
class USkeletalMeshComponent;
class UWidgetComponent;
class UAnimationAsset;
class UParticleSystem;
class UTexture2D;

UCLASS(Abstract, Blueprintable)
class ATOMICHEARTS_API AAWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AAWeaponBase();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void OnRep_Owner() override;

	// --- Weapon Info ---
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Info")
	FText WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Info")
	FText WeaponDescription;

	UPROPERTY(EditAnywhere, Category = "Weapon Info")
	EWeaponSlot WeaponSlot = EWeaponSlot::EWS_Primary;

	UPROPERTY(EditAnywhere, Category = "Weapon Info")
	EAmmoType AmmoType = EAmmoType::EAT_Ballistic;

	// --- Weapon Stats ---
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Stats")
	FWeaponStats Stats;

	// --- Ammo ---
	UPROPERTY(EditAnywhere, Category = "Ammo")
	int32 MagazineSize = 30;

	UPROPERTY(EditAnywhere, Category = "Ammo")
	int32 MaxReserveAmmo = 120;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Ammo")
	int32 CurrentAmmo;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Ammo")
	int32 ReserveAmmo;

	// --- Mesh & Attachment ---
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditAnywhere, Category = "Attachment")
	FName AttachmentSocket = NAME_None;

	UPROPERTY(EditAnywhere, Category = "Attachment")
	FName MuzzleFlashSocket = FName("MuzzleFlash");

	// --- Fire & Effects ---
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fire")
	float FireRate = 0.25f;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TObjectPtr<UAnimationAsset> FireAnimation;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TObjectPtr<USoundCue> FireSound;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TObjectPtr<USoundCue> EmptyMagSound;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TObjectPtr<UParticleSystem> MuzzleEffect;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TObjectPtr<UParticleSystem> ImpactEffect;

	// --- HUD / Crosshair ---
	UPROPERTY(EditAnywhere, Category = "UI")
	TObjectPtr<UTexture2D> CrosshairTexture;

	UPROPERTY(EditAnywhere, Category = "UI")
	TObjectPtr<UTexture2D> WeaponIcon;

	UPROPERTY(EditAnywhere, Category = "UI")
	TObjectPtr<UWidgetComponent> PickupWidget;

	// --- AI Generation ---
	UPROPERTY(EditAnywhere, Category = "AI")
	float AIAccuracy = 0.7f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float AIAimTime = 0.5f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float AIEngagementRange = 3000.f;

public:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Fire(const FVector& HitTarget);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Reload();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StopFire();

	UFUNCTION(Server, Reliable)
	void ServerFire(const FVector& HitTarget);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastFireEffects(const FVector& Location, const FVector& HitLocation);

	bool CanFire() const;
	bool IsMagEmpty() const { return CurrentAmmo <= 0; }
	bool IsMagFull() const { return CurrentAmmo >= MagazineSize; }

	UFUNCTION(BlueprintPure, Category = "Weapon")
	float GetZoomedFOV() const { return ZoomedFOV; }

protected:
	virtual void BeginPlay() override;
	virtual void FireHitScan(const FVector& TraceStart, const FVector& TraceEnd);
	virtual bool TraceHit(const FVector& Start, const FVector& End, FHitResult& OutHit);
	void SpendRound();
	void PlayFireEffects(const FVector& MuzzleLocation, const FVector& HitLocation);
	UAbilitySystemComponent* GetOwnerASC() const;
	void ApplyAmmoConsumptionGAS();

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	FTimerHandle FireTimerHandle;
	bool bIsFiring = false;

	UPROPERTY(EditAnywhere, Category = "Aiming")
	float ZoomedFOV = 30.f;

	UPROPERTY(EditAnywhere, Category = "Aiming")
	float ZoomInterpSpeed = 20.f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> SphereComp;
};
