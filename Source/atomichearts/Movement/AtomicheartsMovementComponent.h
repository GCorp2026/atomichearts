// Copyright (c) 2026 Atomic Hearts Team. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AtomicheartsMovementComponent.generated.h"

class AAtomichartsCharacter;

/** EMovementState - Cyberpunk movement states */
UENUM(BlueprintType)
enum class ECyberMovementState : uint8
{
    Normal,
    Sprinting,
    Sliding,
    Dodging,
    WallRunning
};

/**
 * UAtomicheartsMovementComponent - Cyberpunk movement system
 * Handles: Sprint, Slide, Double Jump, Dodge, Wall Run
 */
UCLASS()
class ATOMICHEARTS_API UAtomicheartsMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()

public:
    UAtomicheartsMovementComponent();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void UpdateFromCompressedFlags(uint8 Flags) override;
    virtual void OnMovementModeChanged(EMovementMode PreviousMode, uint8 PreviousCustomMode) override;

    // Sprint
    UFUNCTION(BlueprintCallable, Category = "Cyber Movement")
    void StartSprint();

    UFUNCTION(BlueprintCallable, Category = "Cyber Movement")
    void StopSprint();

    UFUNCTION(BlueprintPure, Category = "Cyber Movement")
    bool IsSprinting() const { return bIsSprinting; }

    // Slide
    UFUNCTION(BlueprintCallable, Category = "Cyber Movement")
    void StartSlide();

    UFUNCTION(BlueprintCallable, Category = "Cyber Movement")
    void StopSlide();

    UFUNCTION(BlueprintPure, Category = "Cyber Movement")
    bool IsSliding() const { return CurrentMovementState == ECyberMovementState::Sliding; }

    // Double Jump
    UFUNCTION(BlueprintCallable, Category = "Cyber Movement")
    void DoubleJump();

    UFUNCTION(BlueprintPure, Category = "Cyber Movement")
    bool CanDoubleJump() const;

    UFUNCTION(BlueprintPure, Category = "Cyber Movement")
    bool HasDoubleJumped() const { return bHasDoubleJumped; }

    // Dodge
    UFUNCTION(BlueprintCallable, Category = "Cyber Movement")
    void Dodge(const FVector& Direction);

    UFUNCTION(BlueprintPure, Category = "Cyber Movement")
    bool CanDodge() const;

    UFUNCTION(BlueprintPure, Category = "Cyber Movement")
    bool IsDodging() const { return CurrentMovementState == ECyberMovementState::Dodging; }

    // Wall Run (delegated to character)
    UFUNCTION(BlueprintCallable, Category = "Cyber Movement")
    void StartWallRun(bool bRightWall);

    UFUNCTION(BlueprintCallable, Category = "Cyber Movement")
    void StopWallRun();

    // State
    UFUNCTION(BlueprintPure, Category = "Cyber Movement")
    ECyberMovementState GetCurrentState() const { return CurrentMovementState; }

    // Speed multipliers
    UFUNCTION(BlueprintPure, Category = "Cyber Movement")
    float GetSpeedMultiplier() const;

protected:
    virtual void BeginPlay() override;

private:
    // Server validation
    UFUNCTION(Server, Reliable, WithValidation)
    void ServerSetSprinting(bool bSprinting);

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerStartSlide();

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerDodge(const FVector_NetQuantize& Direction);

    void ResetDoubleJump();
    void OnDodgeCooldownFinished();
    void ApplySlidePhysics();
    void ExitSlidePhysics();

public:
    // Config
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprint")
    float SprintSpeedMultiplier = 1.5f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprint")
    float SprintMinSpeedThreshold = 200.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slide")
    float SlideSpeed = 600.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slide")
    float SlideDuration = 0.8f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slide")
    float SlideGravityScale = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slide")
    float SlideEnterSpeedThreshold = 400.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Double Jump")
    float DoubleJumpVelocity = 600.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dodge")
    float DodgeDistance = 300.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dodge")
    float DodgeDuration = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dodge")
    float DodgeCooldown = 2.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dodge")
    float DodgeSpeed = 1200.f;

    // Replicated state
    UPROPERTY(Replicated)
    ECyberMovementState CurrentMovementState = ECyberMovementState::Normal;

protected:
    // Internal state
    bool bIsSprinting = false;
    bool bHasDoubleJumped = false;
    bool bWantsToSlide = false;

    FTimerHandle DoubleJumpResetTimerHandle;
    FTimerHandle DodgeCooldownTimerHandle;

    UPROPERTY(Replicated)
    bool bDodgeOnCooldown = false;

    // Owner reference (cached for performance)
    TWeakObjectPtr<AAtomichartsCharacter> OwnerCharacter;
};