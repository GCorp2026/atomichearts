// Copyright (c) 2024 Atomichearts. All rights reserved.
#pragma once
#include "CoreMinimal.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "NPCCharacter.generated.h"

class UDialogueComponent;

/** ENPCType - Base NPC classification */
UENUM(BlueprintType) enum class ENPCType : uint8 { Civilian, Merchant, Guard, QuestGiver, Vendor, Informant, Enemy };

/** ENPCState - NPC behavior state */
UENUM(BlueprintType) enum class ENPCState : uint8 { Idle, Patrolling, Alert, Hostile, Conversing, Sleeping };

/** FDialoOption - Single dialogue choice */
USTRUCT(BlueprintType) struct FDialoOption
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText OptionText;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName NextNodeID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> RequiredQuestIDs;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> RewardQuestIDs;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ReputationCost = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bEndsDialogue = false;
};

/** FDialogueNode - Dialogue tree node */
USTRUCT(BlueprintType) struct FDialogueNode
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName NodeID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText SpeakerText;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDialoOption> Options;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bIsRootNode = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float DisplayDuration = 0.f;
};

/** UDialogueComponent - Handles NPC dialogue trees */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ATOMICHEARTS_API UDialogueComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UDialogueComponent();
    UFUNCTION(BlueprintCallable) void StartDialogue(AActor* Player);
    UFUNCTION(BlueprintCallable) void SelectOption(int32 OptionIndex);
    UFUNCTION(BlueprintCallable) void EndDialogue();
    UFUNCTION(BlueprintPure) bool HasActiveDialogue() const { return bDialogueActive; }
    UFUNCTION(BlueprintPure) FDialogueNode GetCurrentNode() const { return CurrentNode; }
    UFUNCTION(BlueprintPure) TArray<FDialoOption> GetAvailableOptions() const;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDialogueNode> DialogueTree;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName RootNodeID = NAME_None;
    UPROPERTY(BlueprintAssignable) FOnDialogueNodeChanged OnNodeChanged;
    UPROPERTY(BlueprintAssignable) FOnDialogueEnded OnDialogueEnded;
protected:
    UPROPERTY(VisibleAnywhere) bool bDialogueActive = false;
    UPROPERTY(Replicated) AActor* DialoguePartner = nullptr;
    UPROPERTY(Replicated) FDialogueNode CurrentNode;
    void FindRootNode();
    bool CanSelectOption(const FDialoOption& Option) const;
};

/** ANPCCharacter - Base NPC character with dialogue and quest system */
UCLASS()
class ATOMICHEARTS_API ANPCCharacter : public ABlasterCharacter
{
    GENERATED_BODY()
public:
    ANPCCharacter();
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void Tick(float DeltaTime) override;

    // NPC Config
    UFUNCTION(BlueprintPure) ENPCType GetNPCType() const { return NPCType; }
    UFUNCTION(BlueprintCallable) void SetNPCType(ENPCType NewType);
    UFUNCTION(BlueprintPure) ENPCState GetNPCState() const { return NPCState; }
    UFUNCTION(BlueprintCallable) void SetNPCState(ENPCState NewState);

    // Dialogue & Interaction
    UFUNCTION(BlueprintPure) UDialogueComponent* GetDialogueComponent() const { return DialogueComp; }
    UFUNCTION(BlueprintCallable) void StartDialogue(AActor* Player);
    UFUNCTION(BlueprintCallable) void Interact(AActor* Interactor);
    UFUNCTION(BlueprintPure) bool CanInteract() const;
    UFUNCTION(BlueprintPure) FText GetInteractionPrompt() const;

    // Quest System
    UFUNCTION(BlueprintCallable) void AssignQuest(const FName& QuestID);
    UFUNCTION(BlueprintCallable) void CompleteQuest(const FName& QuestID);
    UFUNCTION(BlueprintPure) bool HasQuest(const FName& QuestID) const;
    UFUNCTION(BlueprintPure) TArray<FName> GetActiveQuests() const { return ActiveQuests; }
    UFUNCTION(BlueprintPure) TArray<FName> GetCompletedQuests() const { return CompletedQuests; }

    // Reputation
    UFUNCTION(BlueprintCallable) void ModifyReputation(float Amount);
    UFUNCTION(BlueprintPure) float GetReputation() const { return Reputation; }

protected:
    virtual void BeginPlay() override;
    UPROPERTY(Replicated) ENPCType NPCType = ENPCType::Civilian;
    UPROPERTY(Replicated) ENPCState NPCState = ENPCState::Idle;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true")) UDialogueComponent* DialogueComp;
    UPROPERTY(EditAnywhere) FText InteractionPrompt = FText::FromString(TEXT("Talk"));
    UPROPERTY(EditAnywhere) float InteractionRange = 200.f;
    UPROPERTY(EditAnywhere) bool bCanInteract = true;
    UPROPERTY(Replicated) TArray<FName> ActiveQuests;
    UPROPERTY(Replicated) TArray<FName> CompletedQuests;
    UPROPERTY(Replicated) TArray<FName> AvailableQuests;
    UPROPERTY(Replicated) float Reputation = 50.f;
    UPROPERTY(EditAnywhere) float PatrolRadius = 500.f;
    UPROPERTY(EditAnywhere) float AlertRadius = 1000.f;
    FVector PatrolCenter;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDialogueNodeChanged, FDialogueNode, Node, AActor*, Player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueEnded, AActor*, Player);
