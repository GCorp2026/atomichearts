// Copyright (c) 2024 Atomichearts. All rights reserved.
#pragma once
#include "CoreMinimal.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "EClassType.h"
#include "UClassAbilityComponent.h"
#include "UClassStatsComponent.h"
#include "AtomicheartsCharacter.generated.h"

class UCurveFloat;

/** EFaction - Faction alignment system */
UENUM(BlueprintType) enum class EFaction : uint8 { Neutral = 0, Syndicate, Corporate, Resistance, Nomad };

/** ESubclassType - Character subclass types */
UENUM(BlueprintType) enum class ESubclassType : uint8 { Tech, Chrome, Neon };

/** FCyberwareUpgrade - Cyberware stat boost definition */
USTRUCT(BlueprintType) struct FCyberwareUpgrade
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName UpgradeName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float SpeedBonus = 0.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float DamageBonus = 0.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float ArmorBonus = 0.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bActive = false;
};

/** UCyberwareComponent - Handles cyberware upgrades */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ATOMICHEARTS_API UCyberwareComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UCyberwareComponent();
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    UFUNCTION(BlueprintCallable) void InstallCyberware(const FCyberwareUpgrade& Upgrade);
    UFUNCTION(BlueprintCallable) void RemoveCyberware(const FName& UpgradeName);
    UFUNCTION(BlueprintPure) float GetTotalSpeedBonus() const;
    UFUNCTION(BlueprintPure) float GetTotalDamageBonus() const;
    UFUNCTION(BlueprintPure) float GetTotalArmorBonus() const;
protected:
    UPROPERTY(Replicated, VisibleAnywhere) TArray<FCyberwareUpgrade> InstalledCyberware;
};

/** UInteractionComponent - Handles quest interactions */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ATOMICHEARTS_API UInteractionComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UInteractionComponent();
    UFUNCTION(BlueprintCallable) void Interact(AActor* Interactor);
    UFUNCTION(BlueprintCallable) void SetInteractable(bool bCanInteract);
    UFUNCTION(BlueprintPure) bool CanInteract() const { return bIsInteractable; }
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText InteractionPrompt;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float InteractionRange = 200.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> QuestIDs;
protected:
    UPROPERTY(Replicated, EditAnywhere) bool bIsInteractable = true;
};

/** AAtomichartsCharacter - Main player character with cyberpunk movement */
UCLASS()
class ATOMICHEARTS_API AAtomichartsCharacter : public ABlasterCharacter
{
    GENERATED_BODY()
public:
    AAtomichartsCharacter();
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void Tick(float DeltaTime) override;

    // Cyberpunk Movement
    UFUNCTION(BlueprintCallable) void StartWallRun(bool bRightWall);
    UFUNCTION(BlueprintCallable) void StopWallRun();
    UFUNCTION(BlueprintCallable) void LaunchGrapple(const FVector& TargetLocation);
    UFUNCTION(BlueprintPure) bool IsWallRunning() const { return bIsWallRunning; }
    UFUNCTION(BlueprintPure) bool IsGrappling() const { return bIsGrappling; }

    // Faction System
    UFUNCTION(BlueprintCallable) void SetFaction(EFaction NewFaction);
    UFUNCTION(BlueprintPure) EFaction GetFaction() const { return CurrentFaction; }
    UFUNCTION(BlueprintPure) float GetFactionStanding(EFaction OtherFaction) const;

    // Subclass
    UFUNCTION(BlueprintCallable) void SetSubclass(ESubclassType NewSubclass);
    UFUNCTION(BlueprintPure) ESubclassType GetSubclass() const { return SubclassType; }

    // Class System (Destiny-style)
    UFUNCTION(BlueprintCallable) void SetClassType(EClassType NewClass);
    UFUNCTION(BlueprintPure) EClassType GetClassType() const { return ClassType; }
    UFUNCTION(BlueprintPure) UCyberwareComponent* GetCyberwareComponent() const { return CyberwareComponent; }
    UFUNCTION(BlueprintPure) UClassAbilityComponent* GetClassAbilityComponent() const { return ClassAbilityComponent; }
    UFUNCTION(BlueprintPure) UClassStatsComponent* GetClassStatsComponent() const { return ClassStatsComponent; }

    // Ability activation (called from ability component)
    UFUNCTION(BlueprintCallable) void OnAbilityActivated(EAbilityType AbilityType);

    // Cyberware & Attachment
    UFUNCTION(BlueprintPure) UCyberwareComponent* GetCyberwareComponent() const { return CyberwareComponent; }
    UFUNCTION(BlueprintCallable) void AttachWeaponToPoint(AActor* Weapon, const FName& PointName);
    UFUNCTION(BlueprintCallable) void RemoveWeaponFromPoint(const FName& PointName);

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    UFUNCTION() void OnRep_FactionChanged();
    UFUNCTION() void OnRep_SubclassChanged();
private:
    void TraceWallRun();
    void ApplyCyberwareBonuses();

    // Movement State
    UPROPERTY(Replicated) bool bIsWallRunning = false;
    UPROPERTY(Replicated) bool bRightWallRunning = false;
    UPROPERTY(Replicated) bool bIsGrappling = false;
    UPROPERTY(EditAnywhere) float WallRunSpeed = 800.f;
    UPROPERTY(EditAnywhere) float WallRunDuration = 2.f;
    UPROPERTY(EditAnywhere) float GrappleStrength = 1500.f;
    UPROPERTY(EditAnywhere) float GrappleCooldown = 3.f;
    UPROPERTY(EditAnywhere) float WallTraceDistance = 100.f;
    FTimerHandle WallRunTimerHandle, GrappleTimerHandle;
    FVector WallRunNormal;

    // Faction & Subclass
    UPROPERTY(Replicated, OnRep = OnRep_FactionChanged) EFaction CurrentFaction = EFaction::Neutral;
    UPROPERTY(EditAnywhere) TMap<EFaction, float> FactionStandings;
    UPROPERTY(Replicated, OnRep = OnRep_SubclassChanged) ESubclassType SubclassType = ESubclassType::Neon;
    UPROPERTY(Replicated) EClassType ClassType = EClassType::TechMage;

    // Delegate for ability effects
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilityEffect, EAbilityType, AbilityType, bool, bSuccess);
    UPROPERTY(BlueprintAssignable)
    FOnAbilityEffect OnAbilityEffect;

    // Components
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
    UCyberwareComponent* CyberwareComponent;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
    UInteractionComponent* InteractionComponent;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
    UClassAbilityComponent* ClassAbilityComponent;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
    UClassStatsComponent* ClassStatsComponent;

    // Weapon Attachment
    UPROPERTY(EditAnywhere) TMap<FName, FName> WeaponAttachmentSockets;
    UPROPERTY(Replicated) TArray<AActor*> AttachedWeapons;
};
