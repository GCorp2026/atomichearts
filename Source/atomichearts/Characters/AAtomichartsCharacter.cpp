// Copyright (c) 2024 Atomichearts. All rights reserved.

#include "Characters/AAtomichartsCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsSettings.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"

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

void AAtomichartsCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AAtomichartsCharacter, bIsWallRunning);
    DOREPLIFETIME(AAtomichartsCharacter, bRightWallRunning);
    DOREPLIFETIME(AAtomichartsCharacter, bIsGrappling);
    DOREPLIFETIME(AAtomichartsCharacter, CurrentFaction);
    DOREPLIFETIME(AAtomichartsCharacter, SubclassType);
    DOREPLIFETIME(AAtomichartsCharacter, AttachedWeapons);
}

void AAtomichartsCharacter::BeginPlay()
{
    Super::BeginPlay();

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
            // Additional input bindings can be added here
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
