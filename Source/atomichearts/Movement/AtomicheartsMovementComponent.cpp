// Copyright (c) 2026 Atomic Hearts Team. All Rights Reserved.

#include "Movement/AtomicheartsMovementComponent.h"
#include "Characters/AAtomichartsCharacter.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"

UAtomicheartsMovementComponent::UAtomicheartsMovementComponent()
{
    bReplicates = true;
    SetIsReplicated(true);

    // Cyberpunk movement config
    SprintSpeedMultiplier = 1.5f;
    SprintMinSpeedThreshold = 200.f;

    SlideSpeed = 600.f;
    SlideDuration = 0.8f;
    SlideGravityScale = 0.3f;
    SlideEnterSpeedThreshold = 400.f;

    DoubleJumpVelocity = 600.f;

    DodgeDistance = 300.f;
    DodgeDuration = 0.3f;
    DodgeCooldown = 2.f;
    DodgeSpeed = 1200.f;

    // Network optimization
    NetworkUpdateInterval = 0.1f;
}

void UAtomicheartsMovementComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UAtomicheartsMovementComponent, CurrentMovementState);
    DOREPLIFETIME(UAtomicheartsMovementComponent, bDodgeOnCooldown);
}

void UAtomicheartsMovementComponent::BeginPlay()
{
    Super::BeginPlay();

    // Cache owner character
    OwnerCharacter = Cast<AAtomichartsCharacter>(GetOwner());
}

void UAtomicheartsMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
    Super::UpdateFromCompressedFlags(Flags);

    // Sync with server state
    bIsSprinting = (Flags & 0x01) != 0;
}

void UAtomicheartsMovementComponent::OnMovementModeChanged(EMovementMode PreviousMode, uint8 PreviousCustomMode)
{
    Super::OnMovementModeChanged(PreviousMode, PreviousCustomMode);

    // Reset sprint if walking
    if (MovementMode == MOVE_Walking && PreviousMode == MOVE_Falling)
    {
        bHasDoubleJumped = false;
    }
}

// =============================================
// SPRINT
// =============================================

void UAtomicheartsMovementComponent::StartSprint()
{
    if (!OwnerCharacter.IsValid())
        return;

    // Can't sprint while sliding or dodging
    if (CurrentMovementState == ECyberMovementState::Sliding ||
        CurrentMovementState == ECyberMovementState::Dodging)
        return;

    // Check if moving fast enough
    if (Velocity.Size() < SprintMinSpeedThreshold)
        return;

    bIsSprinting = true;

    if (HasAuthority())
    {
        CurrentMovementState = ECyberMovementState::Sprinting;
    }
    else
    {
        ServerSetSprinting(true);
    }
}

void UAtomicheartsMovementComponent::StopSprint()
{
    bIsSprinting = false;

    if (HasAuthority() && CurrentMovementState == ECyberMovementState::Sprinting)
    {
        CurrentMovementState = ECyberMovementState::Normal;
    }

    if (!HasAuthority())
    {
        ServerSetSprinting(false);
    }
}

void UAtomicheartsMovementComponent::ServerSetSprinting_Implementation(bool bSprinting)
{
    if (bSprinting)
    {
        StartSprint();
    }
    else
    {
        StopSprint();
    }
}

bool UAtomicheartsMovementComponent::ServerSetSprinting_Validate(bool bSprinting)
{
    return true;
}

// =============================================
// SLIDE
// =============================================

void UAtomicheartsMovementComponent::StartSlide()
{
    if (!OwnerCharacter.IsValid())
        return;

    // Can only slide while sprinting or falling with momentum
    if (CurrentMovementState == ECyberMovementState::Dodging)
        return;

    // Need minimum speed to slide
    if (Velocity.Size() < SlideEnterSpeedThreshold)
        return;

    CurrentMovementState = ECyberMovementState::Sliding;

    // Store current velocity direction for slide momentum
    FVector SlideDirection = Velocity.GetSafeNormal();

    // Apply slide physics
    ApplySlidePhysics();

    // Set timer to end slide
    FTimerHandle SlideTimerHandle;
    OwnerCharacter->GetWorldTimerManager().SetTimer(
        SlideTimerHandle,
        [this]()
        {
            StopSlide();
        },
        SlideDuration,
        false
    );
}

void UAtomicheartsMovementComponent::StopSlide()
{
    if (CurrentMovementState != ECyberMovementState::Sliding)
        return;

    ExitSlidePhysics();

    if (bIsSprinting)
    {
        CurrentMovementState = ECyberMovementState::Sprinting;
    }
    else
    {
        CurrentMovementState = ECyberMovementState::Normal;
    }
}

void UAtomicheartsMovementComponent::ApplySlidePhysics()
{
    UCharacterMovementComponent* Movement = GetCharacterMovement();
    if (!Movement)
        return;

    // Reduce gravity for sliding
    Movement->GravityScale = SlideGravityScale;

    // Clamp to slide speed while maintaining direction
    FVector SlideVelocity = Velocity;
    SlideVelocity.Z = 0.f; // No vertical component during slide

    if (SlideVelocity.Size() > SlideSpeed)
    {
        SlideVelocity = SlideVelocity.GetSafeNormal() * SlideSpeed;
    }

    Velocity = SlideVelocity;
}

void UAtomicheartsMovementComponent::ExitSlidePhysics()
{
    UCharacterMovementComponent* Movement = GetCharacterMovement();
    if (Movement)
    {
        Movement->GravityScale = 1.f;
    }
}

void UAtomicheartsMovementComponent::ServerStartSlide_Implementation()
{
    StartSlide();
}

bool UAtomicheartsMovementComponent::ServerStartSlide_Validate()
{
    return true;
}

// =============================================
// DOUBLE JUMP
// =============================================

void UAtomicheartsMovementComponent::DoubleJump()
{
    if (!CanDoubleJump())
        return;

    bHasDoubleJumped = true;

    // Apply upward velocity
    FVector JumpVelocity = FVector(0.f, 0.f, DoubleJumpVelocity);

    // Preserve some horizontal momentum
    FVector HorizontalMomentum = Velocity;
    HorizontalMomentum.Z = 0.f;
    JumpVelocity += HorizontalMomentum * 0.3f;

    Launch(JumpVelocity);

    // Reset double jump when landing
    OwnerCharacter->GetWorldTimerManager().SetTimer(
        DoubleJumpResetTimerHandle,
        this,
        &UAtomicheartsMovementComponent::ResetDoubleJump,
        0.5f,
        false
    );
}

bool UAtomicheartsMovementComponent::CanDoubleJump() const
{
    if (bHasDoubleJumped)
        return false;

    if (IsFalling())
        return true;

    // Allow double jump immediately after leaving ground (coyote time)
    return true;
}

void UAtomicheartsMovementComponent::ResetDoubleJump()
{
    bHasDoubleJumped = false;
}

// =============================================
// DODGE
// =============================================

void UAtomicheartsMovementComponent::Dodge(const FVector& Direction)
{
    if (!CanDodge())
        return;

    if (!OwnerCharacter.IsValid())
        return;

    CurrentMovementState = ECyberMovementState::Dodging;
    bDodgeOnCooldown = true;

    // Launch in dodge direction
    FVector DodgeVelocity = Direction.GetSafeNormal() * DodgeSpeed;
    DodgeVelocity.Z = 0.f;

    Launch(DodgeVelocity);

    // End dodge after duration
    OwnerCharacter->GetWorldTimerManager().SetTimer(
        DodgeCooldownTimerHandle,
        this,
        &UAtomicheartsMovementComponent::OnDodgeCooldownFinished,
        DodgeDuration,
        false
    );
}

bool UAtomicheartsMovementComponent::CanDodge() const
{
    if (bDodgeOnCooldown)
        return false;

    if (CurrentMovementState == ECyberMovementState::Sliding)
        return false;

    return true;
}

void UAtomicheartsMovementComponent::OnDodgeCooldownFinished()
{
    bDodgeOnCooldown = false;

    if (CurrentMovementState == ECyberMovementState::Dodging)
    {
        CurrentMovementState = ECyberMovementState::Normal;
    }
}

void UAtomicheartsMovementComponent::ServerDodge_Implementation(const FVector_NetQuantize& Direction)
{
    Dodge(Direction);
}

bool UAtomicheartsMovementComponent::ServerDodge_Validate(const FVector_NetQuantize& Direction)
{
    return Direction.Size() > 0.1f;
}

// =============================================
// WALL RUN (delegated)
// =============================================

void UAtomicheartsMovementComponent::StartWallRun(bool bRightWall)
{
    if (!OwnerCharacter.IsValid())
        return;

    CurrentMovementState = ECyberMovementState::WallRunning;
    OwnerCharacter->StartWallRun(bRightWall);
}

void UAtomicheartsMovementComponent::StopWallRun()
{
    CurrentMovementState = ECyberMovementState::Normal;

    if (OwnerCharacter.IsValid())
    {
        OwnerCharacter->StopWallRun();
    }
}

// =============================================
// SPEED MULTIPLIER
// =============================================

float UAtomicheartsMovementComponent::GetSpeedMultiplier() const
{
    switch (CurrentMovementState)
    {
    case ECyberMovementState::Sprinting:
        return SprintSpeedMultiplier;
    case ECyberMovementState::Sliding:
        return SlideSpeed / MaxWalkSpeed;
    case ECyberMovementState::Dodging:
        return DodgeSpeed / MaxWalkSpeed;
    case ECyberMovementState::WallRunning:
        return 1.2f;
    default:
        return 1.0f;
    }
}