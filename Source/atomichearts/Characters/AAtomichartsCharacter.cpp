// Copyright (c) 2024 Atomichearts. All rights reserved.

#include "Characters/AAtomichartsCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsSettings.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

// =============================================================================
// UCyberwareComponent Implementation
// =============================================================================

UCyberwareComponent::UCyberwareComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    SetIsReplicated(true);
}

void UCyberwareComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UCyberwareComponent, InstalledCyberware);
}

void UCyberwareComponent::InstallCyberware(const FCyberwareUpgrade& Upgrade)
{
    if (AActor* Owner = GetOwner())
    {
        if (Owner->HasAuthority())
        {
            InstalledCyberware.Add(Upgrade);
            OnRep_InstalledCyberware();
        }
    }
}

void UCyberwareComponent::RemoveCyberware(const FName& UpgradeName)
{
    if (AActor* Owner = GetOwner())
    {
        if (Owner->HasAuthority())
        {
            InstalledCyberware.RemoveAll([&UpgradeName](const FCyberwareUpgrade& U) {
                return U.UpgradeName == UpgradeName;
            });
            OnRep_InstalledCyberware();
        }
    }
}

void UCyberwareComponent::OnRep_InstalledCyberware()
{
    // Broadcast update to UI/HUD
    OnCyberwareUpdated.Broadcast(InstalledCyberware);
}

float UCyberwareComponent::GetTotalSpeedBonus() const
{
    float Total = 0.f;
    for (const FCyberwareUpgrade& U : InstalledCyberware)
    {
        if (U.bActive)
            Total += U.SpeedBonus;
    }
    return Total;
}

float UCyberwareComponent::GetTotalDamageBonus() const
{
    float Total = 0.f;
    for (const FCyberwareUpgrade& U : InstalledCyberware)
    {
        if (U.bActive)
            Total += U.DamageBonus;
    }
    return Total;
}

float UCyberwareComponent::GetTotalArmorBonus() const
{
    float Total = 0.f;
    for (const FCyberwareUpgrade& U : InstalledCyberware)
    {
        if (U.bActive)
            Total += U.ArmorBonus;
    }
    return Total;
}

// =============================================================================
// UInteractionComponent Implementation
// =============================================================================

UInteractionComponent::UInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionComponent::Interact(AActor* Interactor)
{
    if (!bIsInteractable)
        return;

    // Trigger quest events or dialogue
    OnInteract.Broadcast(Interactor, QuestIDs);
}

void UInteractionComponent::SetInteractable(bool bCanInteract)
{
    bIsInteractable = bCanInteract;
    OnInteractableChanged.Broadcast(bCanInteract);
}

// =============================================================================
// AAtomichartsCharacter Implementation
// =============================================================================

AAtomichartsCharacter::AAtomichartsCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

    // Create cyberware component
    CyberwareComponent = CreateDefaultSubobject<UCyberwareComponent>(TEXT("CyberwareComponent"));
    
    // Create interaction component
    InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));

    // Create class ability component
    ClassAbilityComponent = CreateDefaultSubobject<UClassAbilityComponent>(TEXT("ClassAbilityComponent"));

    // Create class stats component
    ClassStatsComponent = CreateDefaultSubobject<UClassStatsComponent>(TEXT("ClassStatsComponent"));

    // Create Time Mage ability set component (crowd control specialist)
    TimeMageAbilities = CreateDefaultSubobject<UTimeMageAbilitySet>(TEXT("TimeMageAbilities"));

    // Create Cyberpunk movement component
    CyberpunkMovement = CreateDefaultSubobject<UAtomicheartsMovementComponent>(TEXT("CyberpunkMovement"));

    // Create Gameplay Ability System components
    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EAbilitySystemReplicationMode::Mixed);

    AttributeSet = CreateDefaultSubobject<UAtomicHeartsAttributeSet>(TEXT("AttributeSet"));

    // Initialize default faction standings
    FactionStandings.Add(EFaction::Syndicate, 50.f);
    FactionStandings.Add(EFaction::Corporate, 50.f);
    FactionStandings.Add(EFaction::Resistance, 50.f);
    FactionStandings.Add(EFaction::Nomad, 50.f);

    // Initialize attachment sockets
    WeaponAttachmentSockets.Add(FName("PrimaryWeapon"), FName("WeaponSocket"));
    WeaponAttachmentSockets.Add(FName("Sidearm"), FName("SidearmSocket"));
    WeaponAttachmentSockets.Add(FName("Melee"), FName("MeleeSocket"));
    WeaponAttachmentSockets.Add(FName("Cyberware"), FName("CyberwareSocket"));
}

UAbilitySystemComponent* AAtomichartsCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void AAtomichartsCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AAtomichartsCharacter, bIsWallRunning);
    DOREPLIFETIME(AAtomichartsCharacter, bRightWallRunning);
    DOREPLIFETIME(AAtomichartsCharacter, bIsGrappling);
    DOREPLIFETIME(AAtomichartsCharacter, CurrentFaction);
    DOREPLIFETIME(AAtomichartsCharacter, SubclassType);
    DOREPLIFETIME(AAtomichartsCharacter, ClassType);
    DOREPLIFETIME(AAtomichartsCharacter, AttachedWeapons);
}

void AAtomichartsCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Initialize Gameplay Ability System
    if (AbilitySystemComponent && AttributeSet)
    {
        AbilitySystemComponent->InitAbilityActorInfo(this, this);
        // Register the AttributeSet with the AbilitySystemComponent
        AbilitySystemComponent->AddAttributeSetSubobject(AttributeSet);
    }

    if (HasAuthority())
    {
        // Apply subclass bonuses
        ApplyCyberwareBonuses();
    }
}

void AAtomichartsCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsWallRunning)
    {
        TraceWallRun();
    }
}

void AAtomichartsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
        {
            // Sprint input (Hold Shift)
            if (InputConfig)
            {
                // Bind sprint (hold)
                if (const UInputAction* SprintAction = InputConfig->FindNativeInputActionForTag(FGameplayTag::RequestGameplayTag(FName("Input.Sprint"))))
                {
                    EnhancedInput->BindAction(SprintAction, ETriggerEvent::Started, this, &AAtomichartsCharacter::SprintPressed);
                    EnhancedInput->BindAction(SprintAction, ETriggerEvent::Completed, this, &AAtomichartsCharacter::SprintReleased);
                }
                // Bind slide (crouch while sprinting)
                if (const UInputAction* SlideAction = InputConfig->FindNativeInputActionForTag(FGameplayTag::RequestGameplayTag(FName("Input.Slide"))))
                {
                    EnhancedInput->BindAction(SlideAction, ETriggerEvent::Triggered, this, &AAtomichartsCharacter::SlidePressed);
                }
                // Bind double jump
                if (const UInputAction* DoubleJumpAction = InputConfig->FindNativeInputActionForTag(FGameplayTag::RequestGameplayTag(FName("Input.DoubleJump"))))
                {
                    EnhancedInput->BindAction(DoubleJumpAction, ETriggerEvent::Triggered, this, &AAtomichartsCharacter::DoubleJumpPressed);
                }
                // Bind dodge (double-tap direction)
                if (const UInputAction* DodgeAction = InputConfig->FindNativeInputActionForTag(FGameplayTag::RequestGameplayTag(FName("Input.Dodge"))))
                {
                    EnhancedInput->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &AAtomichartsCharacter::DodgePressed);
                }
            }
        }
    }
}

void AAtomichartsCharacter::StartWallRun(bool bRightWall)
{
    if (bIsWallRunning || bIsGrappling || GetCharacterMovement()->IsFalling())
        return;

    bIsWallRunning = true;
    bRightWallRunning = bRightWall;

    // Disable gravity while wall running
    UCharacterMovementComponent* Movement = GetCharacterMovement();
    Movement->GravityScale = 0.f;
    Movement->Velocity = FVector(0.f, 0.f, 0.f);

    // Set timer to auto-stop wall run
    GetWorldTimerManager().SetTimer(WallRunTimerHandle, this, &AAtomichartsCharacter::StopWallRun, WallRunDuration, false);

    OnStartWallRun.Broadcast(bRightWall);
}

void AAtomichartsCharacter::StopWallRun()
{
    if (!bIsWallRunning)
        return;

    bIsWallRunning = false;

    UCharacterMovementComponent* Movement = GetCharacterMovement();
    Movement->GravityScale = 1.f;

    GetWorldTimerManager().ClearTimer(WallRunTimerHandle);

    OnStopWallRun.Broadcast();
}

void AAtomichartsCharacter::LaunchGrapple(const FVector& TargetLocation)
{
    if (bIsGrappling || bIsWallRunning)
        return;

    bIsGrappling = true;

    FVector LaunchDirection = (TargetLocation - GetActorLocation()).GetSafeNormal();
    LaunchDirection.Z = FMath::Max(LaunchDirection.Z, 0.3f); // Prevent too downward

    LaunchCharacter(LaunchDirection * GrappleStrength, true, true);

    OnGrappleLaunched.Broadcast(TargetLocation);

    // Cooldown timer
    GetWorldTimerManager().SetTimer(GrappleTimerHandle, [this]()
    {
        bIsGrappling = false;
    }, GrappleCooldown, false);
}

void AAtomichartsCharacter::SetFaction(EFaction NewFaction)
{
    if (!HasAuthority())
        return;

    CurrentFaction = NewFaction;
    OnRep_FactionChanged();
}

void AAtomichartsCharacter::OnRep_FactionChanged()
{
    OnFactionChanged.Broadcast(CurrentFaction);
}

void AAtomichartsCharacter::SetSubclass(ESubclassType NewSubclass)
{
    if (!HasAuthority())
        return;

    SubclassType = NewSubclass;
    OnRep_SubclassChanged();
}

void AAtomichartsCharacter::OnRep_SubclassChanged()
{
    ApplyCyberwareBonuses();
    OnSubclassChanged.Broadcast(SubclassType);
}

float AAtomichartsCharacter::GetFactionStanding(EFaction OtherFaction) const
{
    if (const float* Standing = FactionStandings.Find(OtherFaction))
        return *Standing;
    return 50.f;
}

void AAtomichartsCharacter::AttachWeaponToPoint(AActor* Weapon, const FName& PointName)
{
    if (!HasAuthority() || !Weapon)
        return;

    if (FName* SocketName = WeaponAttachmentSockets.Find(PointName))
    {
        USkeletalMeshComponent* Mesh = GetMesh();
        if (Mesh)
        {
            Weapon->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, *SocketName);
            AttachedWeapons.Add(Weapon);
        }
    }
}

void AAtomichartsCharacter::RemoveWeaponFromPoint(const FName& PointName)
{
    if (!HasAuthority())
        return;

    for (AActor* Weapon : AttachedWeapons)
    {
        if (Weapon)
        {
            FDetachmentTransformRules Rules(EDetachmentRule::KeepWorld, false);
            Weapon->DetachFromActor(Rules);
        }
    }
    AttachedWeapons.Empty();
}

void AAtomichartsCharacter::TraceWallRun()
{
    FVector Start = GetActorLocation();
    FVector RightVector = GetActorRightVector();
    FVector Direction = bRightWallRunning ? RightVector : -RightVector;

    FVector End = Start + Direction * WallTraceDistance;

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, QueryParams))
    {
        WallRunNormal = HitResult.ImpactNormal;
        
        // Apply force to stay on wall
        FVector SlideDirection = FVector::CrossProduct(WallRunNormal, FVector::UpVector);
        if (bRightWallRunning)
            SlideDirection = -SlideDirection;
        
        LaunchCharacter(SlideDirection * WallRunSpeed * 0.5f, true, true);
    }
    else
    {
        // No wall found, stop wall run
        StopWallRun();
    }
}

void AAtomichartsCharacter::SetClassType(EClassType NewClass)
{
    if (!HasAuthority())
        return;

    ClassType = NewClass;

    // Configure ability component for this class
    if (ClassAbilityComponent)
    {
        ClassAbilityComponent->SetClass(NewClass);
    }

    // Configure stats component for this class
    if (ClassStatsComponent)
    {
        ClassStatsComponent->SetClass(NewClass);
    }
}

void AAtomichartsCharacter::OnAbilityActivated(EAbilityType AbilityType)
{
    // Play ability effects based on type
    switch (AbilityType)
    {
    case EAbilityType::TimeStop:
        // Time freeze visual effect
        OnAbilityEffect.Broadcast(AbilityType, true);
        break;
    case EAbilityType::Barricade:
        // Deploy barricade mesh
        OnAbilityEffect.Broadcast(AbilityType, true);
        break;
    case EAbilityType::Dodge:
    case EAbilityType::Vanish:
        // Invisibility / dodge effect
        OnAbilityEffect.Broadcast(AbilityType, true);
        break;
    case EAbilityType::HealingRift:
        // Spawn healing zone
        OnAbilityEffect.Broadcast(AbilityType, true);
        break;
    case EAbilityType::FanTheHammer:
        // Rapid fire effect
        OnAbilityEffect.Broadcast(AbilityType, true);
        break;
    case EAbilityType::Blink:
        // Teleport effect
        OnAbilityEffect.Broadcast(AbilityType, true);
        break;
    default:
        OnAbilityEffect.Broadcast(AbilityType, false);
        break;
    }
}

void AAtomichartsCharacter::ApplyCyberwareBonuses()
{
    if (!CyberwareComponent)
        return;

    UCharacterMovementComponent* Movement = GetCharacterMovement();

    // Apply speed bonus
    float SpeedBonus = CyberwareComponent->GetTotalSpeedBonus();
    if (SpeedBonus > 0.f)
    {
        Movement->MaxWalkSpeed += SpeedBonus;
    }

    // Subclass-specific bonuses
    switch (SubclassType)
    {
    case ESubclassType::Tech:
        // Tech class gets hacking bonuses handled elsewhere
        break;
    case ESubclassType::Chrome:
        // Chrome class gets melee bonuses
        if (UCharacterMovementComponent* Move = GetCharacterMovement())
        {
            Move->MaxWalkSpeed += 100.f; // Chrome is faster
        }
        break;
    case ESubclassType::Neon:
        // Neon class already uses guns, no special bonus here
        break;
    }
}

// =============================================================================
// Cyberpunk Movement Getters
// =============================================================================

bool AAtomichartsCharacter::IsSprinting() const
{
    if (CyberpunkMovement)
    {
        return CyberpunkMovement->IsSprinting();
    }
    return false;
}

bool AAtomichartsCharacter::IsSliding() const
{
    if (CyberpunkMovement)
    {
        return CyberpunkMovement->IsSliding();
    }
    return false;
}

bool AAtomichartsCharacter::CanDoubleJump() const
{
    if (CyberpunkMovement)
    {
        return CyberpunkMovement->CanDoubleJump();
    }
    return false;
}

bool AAtomichartsCharacter::IsDodging() const
{
    if (CyberpunkMovement)
    {
        return CyberpunkMovement->IsDodging();
    }
    return false;
}

// =============================================================================
// Cyberpunk Movement Input Callbacks
// =============================================================================

void AAtomichartsCharacter::SprintPressed()
{
    if (!HasAuthority())
    {
        ServerSprintPressed();
    }
    if (CyberpunkMovement)
    {
        CyberpunkMovement->StartSprint();
    }
}

void AAtomichartsCharacter::SprintReleased()
{
    if (!HasAuthority())
    {
        ServerSprintReleased();
    }
    if (CyberpunkMovement)
    {
        CyberpunkMovement->StopSprint();
    }
}

void AAtomichartsCharacter::SlidePressed()
{
    if (!HasAuthority())
    {
        ServerSlidePressed();
    }
    if (CyberpunkMovement)
    {
        CyberpunkMovement->StartSlide();
    }
}

void AAtomichartsCharacter::DoubleJumpPressed()
{
    if (!HasAuthority())
    {
        ServerDoubleJump();
    }
    if (CyberpunkMovement)
    {
        CyberpunkMovement->DoubleJump();
    }
}

void AAtomichartsCharacter::DodgePressed(const FInputActionValue& Value)
{
    FVector2D DirectionValue = Value.Get<FVector2D>();
    
    // Convert screen direction to world direction
    FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
    FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    FVector DodgeDirection = (ForwardVector * DirectionValue.Y + RightVector * DirectionValue.X).GetSafeNormal();
    
    if (!HasAuthority())
    {
        ServerDodge(DodgeDirection);
    }
    if (CyberpunkMovement)
    {
        CyberpunkMovement->Dodge(DodgeDirection);
    }
}

// =============================================================================
// Server RPCs for Movement Validation
// =============================================================================

void AAtomichartsCharacter::ServerSprintPressed_Implementation()
{
    if (CyberpunkMovement)
    {
        CyberpunkMovement->StartSprint();
    }
}

bool AAtomichartsCharacter::ServerSprintPressed_Validate()
{
    return true;
}

void AAtomichartsCharacter::ServerSprintReleased_Implementation()
{
    if (CyberpunkMovement)
    {
        CyberpunkMovement->StopSprint();
    }
}

bool AAtomichartsCharacter::ServerSprintReleased_Validate()
{
    return true;
}

void AAtomichartsCharacter::ServerSlidePressed_Implementation()
{
    if (CyberpunkMovement)
    {
        CyberpunkMovement->StartSlide();
    }
}

bool AAtomichartsCharacter::ServerSlidePressed_Validate()
{
    return true;
}

void AAtomichartsCharacter::ServerDoubleJump_Implementation()
{
    if (CyberpunkMovement)
    {
        CyberpunkMovement->DoubleJump();
    }
}

bool AAtomichartsCharacter::ServerDoubleJump_Validate()
{
    return true;
}

void AAtomichartsCharacter::ServerDodge_Implementation(const FVector_NetQuantize& Direction)
{
    if (CyberpunkMovement)
    {
        CyberpunkMovement->Dodge(Direction);
    }
}

bool AAtomichartsCharacter::ServerDodge_Validate(const FVector_NetQuantize& Direction)
{
    return Direction.Size() > 0.1f;
}
