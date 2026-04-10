// Copyright 2026 Atomic Hearts Team

#include "Weapons/AWeaponBase.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffects/AmmoConsumptionEffect.h"

AAWeaponBase::AAWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	SetReplicateMovement(true);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetSphereRadius(64.f);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	PickupWidget->SetupAttachment(RootComponent);
	PickupWidget->SetVisibility(false);
}

void AAWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AAWeaponBase::OnSphereOverlap);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &AAWeaponBase::OnSphereEndOverlap);

	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}

void AAWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAWeaponBase, CurrentAmmo);
	DOREPLIFETIME(AAWeaponBase, ReserveAmmo);
}

void AAWeaponBase::OnRep_Owner()
{
	Super::OnRep_Owner();
}

void AAWeaponBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (Character && Character->IsPlayerControlled())
	{
		if (UInteractionComponent* Interact = Character->FindComponentByClass<UInteractionComponent>())
		{
			PickupWidget->SetVisibility(true);
		}
	}
}

void AAWeaponBase::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PickupWidget->SetVisibility(false);
}

bool AAWeaponBase::CanFire() const
{
	return !IsMagEmpty() && !FireTimerHandle.IsValid();
}

void AAWeaponBase::StartFire()
{
	if (!CanFire()) return;

	bIsFiring = true;

	FVector Start;
	FRotator Rotation;
	if (AActor* Owner = GetOwner())
	{
		Owner->GetActorEyesViewPoint(Start, Rotation);
	}
	else
	{
		Start = GetActorLocation();
		Rotation = GetActorRotation();
	}

	FVector End = Start + Rotation.Vector() * Stats.Range;
	Fire(End);
}

void AAWeaponBase::StopFire()
{
	bIsFiring = false;
}

void AAWeaponBase::Fire(const FVector& HitTarget)
{
	if (!CanFire()) return;

	if (HasAuthority())
	{
		FVector Start;
		FRotator Rotation;
		if (AActor* Owner = GetOwner())
		{
			Owner->GetActorEyesViewPoint(Start, Rotation);
		}
		else
		{
			Start = GetActorLocation();
			Rotation = GetActorRotation();
		}

		FVector End = Start + Rotation.Vector() * Stats.Range;
		FireHitScan(Start, End);
		SpendRound();

		MulticastFireEffects(Start, HitTarget);
	}
	else
	{
		ServerFire(HitTarget);
	}

	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AAWeaponBase::StopFire, FireRate, false);
}

void AAWeaponBase::ServerFire_Implementation(const FVector& HitTarget)
{
	FVector Start;
	FRotator Rotation;
	if (AActor* Owner = GetOwner())
	{
		Owner->GetActorEyesViewPoint(Start, Rotation);
	}
	else
	{
		Start = GetActorLocation();
		Rotation = GetActorRotation();
	}

	FVector End = Start + Rotation.Vector() * Stats.Range;
	FireHitScan(Start, End);
	SpendRound();
	MulticastFireEffects(Start, HitTarget);
}

void AAWeaponBase::MulticastFireEffects_Implementation(const FVector& Location, const FVector& HitLocation)
{
	if (FireAnimation && WeaponMesh)
	{
		WeaponMesh->PlayAnimation(FireAnimation, false);
	}

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	const USkeletalMeshSocket* MuzzleSocket = WeaponMesh->GetSocketByName(MuzzleFlashSocket);
	if (MuzzleSocket && MuzzleEffect)
	{
		FTransform MuzzleTransform = MuzzleSocket->GetSocketTransform(WeaponMesh);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleEffect, MuzzleTransform);
	}
}

void AAWeaponBase::FireHitScan(const FVector& TraceStart, const FVector& TraceEnd)
{
	FHitResult Hit;
	if (TraceHit(TraceStart, TraceEnd, Hit))
	{
		float Damage = Stats.Damage;
		FName BoneName = Hit.BoneName;

		if (BoneName == FName("head") || BoneName == FName("Head"))
		{
			Damage *= Stats.HeadshotMultiplier;
		}
		else if (BoneName == FName("leg_l") || BoneName == FName("leg_r") ||
			BoneName == FName("Foot_L") || BoneName == FName("Foot_R"))
		{
			Damage *= Stats.LegshotMultiplier;
		}

		UGameplayStatics::ApplyDamage(
			Hit.GetActor(),
			Damage,
			Cast<APawn>(GetOwner())->GetController(),
			this,
			UDamageType::StaticClass()
		);

		if (ImpactEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint);
		}
	}
}

bool AAWeaponBase::TraceHit(const FVector& Start, const FVector& End, FHitResult& OutHit)
{
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	if (AActor* Owner = GetOwner())
	{
		Params.AddIgnoredActor(Owner);
	}

	return GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Weapon, Params);
}

void AAWeaponBase::SpendRound()
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo - 1, 0, MagazineSize);
	ApplyAmmoConsumptionGAS();

	if (IsMagEmpty() && EmptyMagSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, EmptyMagSound, GetActorLocation());
	}
}

UAbilitySystemComponent* AAWeaponBase::GetOwnerASC() const
{
	AActor* Owner = GetOwner();
	if (!Owner) return nullptr;
	IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Owner);
	if (!ASI) return nullptr;
	return ASI->GetAbilitySystemComponent();
}

void AAWeaponBase::ApplyAmmoConsumptionGAS()
{
	UAbilitySystemComponent* ASC = GetOwnerASC();
	if (!ASC) return;

	FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
	Context.AddSourceObject(this);
	FGameplayEffectSpecHandle Spec = ASC->MakeOutgoingSpec(UAmmoConsumptionEffect::StaticClass(), 1.0f, Context);
	if (Spec.IsValid())
	{
		ASC->ApplyGameplayEffectSpecToSelf(*Spec.Data);
	}
}

void AAWeaponBase::Reload()
{
	if (ReserveAmmo <= 0) return;

	int32 AmmoNeeded = MagazineSize - CurrentAmmo;
	int32 AmmoToReload = FMath::Min(AmmoNeeded, ReserveAmmo);

	CurrentAmmo += AmmoToReload;
	ReserveAmmo -= AmmoToReload;
}
