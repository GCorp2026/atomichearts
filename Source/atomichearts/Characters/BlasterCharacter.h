// Copyright (c) 2026 Atomic Hearts Team. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "InputActionValue.h"
#include "BlasterTypes/BCombatState.h"
#include "BlasterTypes/BTeams.h"
#include "BlasterCharacter.generated.h"

class AAWeaponBase;
class UBlasterCombatComponent;
class UBlasterBuffComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UBInputConfig;
class UWidgetComponent;
class UAnimMontage;
class UCurveFloat;
class ABlasterPlayerController;
class ABlasterPlayerState;
class ABlasterGameMode;

DECLARE_MULTICAST_DELEGATE(FOnLeftGame);

/**
 * ABlasterCharacter - Base TPS character with aim offset, combat, and movement
 * Used as parent for AAtomichartsCharacter
 */
UCLASS()
class ATOMICHEARTS_API ABlasterCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ABlasterCharacter();

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void PostInitializeComponents() override;
    virtual void OnRep_ReplicatedMovement() override;
    virtual void Destroyed() override;

    // Weapon
    UFUNCTION(BlueprintCallable) void EquipPrimaryWeapon();
    UFUNCTION(BlueprintCallable) void EquipSecondaryWeapon();
    UFUNCTION(BlueprintCallable) void SwapWeapons();
    void SetOverlappingWeapon(AAWeaponBase* Weapon);
    void PlayFireMontage(bool bAiming);
    void PlayReloadMontage();
    void PlaySwapMontage();

    UFUNCTION(NetMulticast, Reliable)
    void MulticastHandleDeath(bool bPlayerLeftGame);

    virtual void HandleDeath(bool bPlayerLeftGame);

    // Aiming
    UFUNCTION(BlueprintPure) float GetAO_Yaw() const { return AO_Yaw; }
    UFUNCTION(BlueprintPure) float GetAO_Pitch() const { return AO_Pitch; }

    UFUNCTION(BlueprintPure)
    bool IsWeaponEquipped() const;

    UFUNCTION(BlueprintPure)
    bool IsAiming() const { return bIsAiming; }

    UFUNCTION(BlueprintPure)
    EBCombatState GetCombatState() const;

    UFUNCTION(BlueprintPure)
    AAWeaponBase* GetEquippedWeapon() const;

    UFUNCTION(BlueprintPure)
    UCameraComponent* GetFollowCamera() const { return FollowCamera; }

    UFUNCTION(BlueprintPure)
    UBlasterCombatComponent* GetCombatComp() const { return CombatComp; }

    // Health
    UFUNCTION(BlueprintPure) float GetHealth() const { return Health; }
    UFUNCTION(BlueprintPure) float GetMaxHealth() const { return MaxHealth; }
    UFUNCTION(BlueprintPure) float GetShield() const { return Shield; }
    UFUNCTION(BlueprintPure) float GetMaxShield() const { return MaxShield; }

    void SetHealth(float Amount) { Health = Amount; }
    void SetShield(float Amount) { Shield = Amount; }

    // HUD
    void UpdateHUDHealth();
    void UpdateHUDShield();
    void UpdateHUDAmmo();

    // Movement
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void AimButtonPressed();
    void AimButtonReleased();
    virtual void Jump() override;
    void CrouchButtonPressed();
    void SprintButtonPressed();
    void SprintButtonReleased();

    // Crouch
    UFUNCTION(BlueprintPure) bool IsCrouching() const { return bIsCrouched; }

    // Game
    UFUNCTION(Server, Reliable) void ServerLeaveGame();
    EBTeam GetTeam() const { return Team; }

    UFUNCTION(NetMulticast, Reliable)
    void MulticastGainedTheLead();

    UFUNCTION(NetMulticast, Reliable)
    void MulticastLostTheLead();

public:
    UPROPERTY(Replicated)
    bool bDisableGameplay = false;

    UPROPERTY()
    TArray<FString> LegBoneNames;

    FOnLeftGame OnLeftGameDelegate;

protected:
    virtual void BeginPlay() override;

    void CalculateAO_Pitch();
    float CalculateSpeed();
    void AimOffset(float DeltaTime);
    void SimProxiesTurn();
    void TurnInPlace(float DeltaTime);
    void RotateInPlace(float DeltaTime);

    void OnPlayerStateInitialized();
    UFUNCTION() void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
        AController* InstigatorController, AActor* DamageCauser);

    void PollInit();

private:
    UFUNCTION()
    void OnRep_OverlappingWeapon(AAWeaponBase* LastWeapon);

    UFUNCTION()
    void OnRep_Health(float LastHealth);

    UFUNCTION()
    void OnRep_Shield(float LastShield);

    UFUNCTION(Server, Reliable)
    void ServerEquip();

    UFUNCTION(Server, Reliable)
    void ServerSwapButtonPressed();

    UFUNCTION(Server, Reliable)
    void ServerSetAiming(bool bAiming);

    UFUNCTION(Server, Reliable)
    void ServerSetSprinting(bool bSprinting);

    void HideCharacterIfCameraClose();
    void StartDissolve();
    UFUNCTION() void UpdateDissolveMaterial(float DissolveValue);

private:
    UPROPERTY()
    TObjectPtr<ABlasterPlayerController> BlasterPC;

    UPROPERTY()
    TObjectPtr<ABlasterPlayerState> BlasterPS;

    UPROPERTY()
    TObjectPtr<ABlasterGameMode> BlasterGameMode;

    // Camera
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TObjectPtr<UCameraComponent> FollowCamera;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
    float CameraThreshold = 100.f;

    // Overhead widget
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TObjectPtr<UWidgetComponent> OverheadWidget;

    // Overlapping weapon
    UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
    TObjectPtr<AAWeaponBase> OverlappingWeapon;

    // Combat component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    TObjectPtr<UBlasterCombatComponent> CombatComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    TObjectPtr<UBlasterBuffComponent> BuffComponent;

    // Aim offset
    float AO_Yaw = 0.f;
    float AO_Pitch = 0.f;
    float InterpAO_Yaw = 0.f;
    FRotator StartingAimRotation;

    // Animation montages
    UPROPERTY(EditAnywhere, Category = "Combat")
    TObjectPtr<UAnimMontage> FireWeaponMontage;

    UPROPERTY(EditAnywhere, Category = "Combat")
    TObjectPtr<UAnimMontage> ReloadWeaponMontage;

    UPROPERTY(EditAnywhere, Category = "Combat")
    TObjectPtr<UAnimMontage> SwapWeaponMontage;

    // Attributes
    UPROPERTY(EditAnywhere, Category = "Attributes")
    float MaxHealth = 100.f;

    UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Health, Category = "Attributes")
    float Health = 100.f;

    UPROPERTY(EditAnywhere, Category = "Attributes")
    float MaxShield = 100.f;

    UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Shield, Category = "Attributes")
    float Shield = 50.f;

    // Team
    UPROPERTY(Replicated)
    EBTeam Team = EBTeam::EBT_NoTeam;

    // State
    bool bDead = false;
    UPROPERTY(EditDefaultsOnly, Category = "Death")
    float RespawnDelay = 3.f;

    FTimerHandle RespawnTimerHandle;

    // Input
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UBInputConfig> InputConfig;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

    // Aim state
    UPROPERTY(Replicated)
    bool bIsAiming = false;

    // Sprint state
    UPROPERTY(Replicated)
    bool bIsSprinting = false;

    // Dissolve
    UPROPERTY(VisibleAnywhere, Category = "Death")
    TObjectPtr<UTimelineComponent> DissolveTimelineComp;

    FOnTimelineFloat DissolveTrackDelegate;

    UPROPERTY(EditAnywhere, Category = "Death")
    TObjectPtr<UCurveFloat> DissolveCurve;

    UPROPERTY(VisibleAnywhere, Category = "Death")
    TObjectPtr<UMaterialInstanceDynamic> DissolveDynamicMaterialInstance;

    UPROPERTY(EditAnywhere, Category = "Death")
    TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

    // Movement
    UPROPERTY(EditAnywhere, Category = "Movement")
    float SprintSpeedMultiplier = 1.5f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float CrouchSpeed = 300.f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float StandingCapsuleHalfHeight = 96.f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float CrouchingCapsuleHalfHeight = 48.f;
};