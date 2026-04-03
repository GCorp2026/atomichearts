#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UProgressionComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ATOMICHEARTS_API UProgressionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UProgressionComponent();

    // XP System
    UFUNCTION(BlueprintCallable, Category = "Progression")
    void AddXP(int32 Amount);

    UFUNCTION(BlueprintPure, Category = "Progression")
    int32 GetXP() const { return XP; }

    UFUNCTION(BlueprintPure, Category = "Progression")
    int32 GetXPToNextLevel() const;

    UFUNCTION(BlueprintPure, Category = "Progression")
    int32 GetLevel() const { return Level; }

    // Light Level (1-2000)
    UFUNCTION(BlueprintPure, Category = "Progression")
    int32 GetLightLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Progression")
    void SetLightLevel(int32 NewLevel);

    UFUNCTION(BlueprintPure, Category = "Progression")
    float GetXPProgress() const;

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Progression")
    int32 XP = 0;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Progression")
    int32 Level = 1;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Progression")
    int32 LightLevel = 1;

    UPROPERTY(EditAnywhere, Category = "Progression")
    int32 XPPerLevel = 1000;

    int32 CalculateLightLevelFromLevel() const;
};
