// Copyright (c) 2024 Atomichearts. All rights reserved.

#include "Characters/ANPCCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"

// =============================================================================
// UDialogueComponent Implementation
// =============================================================================

UDialogueComponent::UDialogueComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    SetIsReplicated(true);
}

void UDialogueComponent::StartDialogue(AActor* Player)
{
    if (!ensure(DialogueTree.Num() > 0))
        return;

    DialoguePartner = Player;
    bDialogueActive = true;

    FindRootNode();
    OnNodeChanged.Broadcast(CurrentNode, Player);
}

void UDialogueComponent::SelectOption(int32 OptionIndex)
{
    if (!bDialogueActive)
        return;

    TArray<FDialoOption> Available = GetAvailableOptions();
    if (!Available.IsValidIndex(OptionIndex))
        return;

    const FDialoOption& Selected = Available[OptionIndex];

    if (Selected.bEndsDialogue)
    {
        EndDialogue();
        return;
    }

    // Find next node
    for (const FDialogueNode& Node : DialogueTree)
    {
        if (Node.NodeID == Selected.NextNodeID)
        {
            CurrentNode = Node;
            OnNodeChanged.Broadcast(CurrentNode, DialoguePartner);
            break;
        }
    }
}

void UDialogueComponent::EndDialogue()
{
    bDialogueActive = false;
    OnDialogueEnded.Broadcast(DialoguePartner);
    DialoguePartner = nullptr;
}

TArray<FDialoOption> UDialogueComponent::GetAvailableOptions() const
{
    TArray<FDialoOption> Available;

    for (const FDialoOption& Option : CurrentNode.Options)
    {
        if (CanSelectOption(Option))
        {
            Available.Add(Option);
        }
    }

    return Available;
}

void UDialogueComponent::FindRootNode()
{
    for (const FDialogueNode& Node : DialogueTree)
    {
        if (Node.bIsRootNode)
        {
            CurrentNode = Node;
            return;
        }
    }

    // Fallback to first node if no root marked
    if (DialogueTree.Num() > 0)
    {
        CurrentNode = DialogueTree[0];
    }
}

bool UDialogueComponent::CanSelectOption(const FDialoOption& Option) const
{
    // Check required quests
    for (const FName& QuestID : Option.RequiredQuestIDs)
    {
        // Would check quest system here
    }

    // Check reputation cost
    // Would check NPC reputation here

    return true;
}

// =============================================================================
// ANPCCharacter Implementation
// =============================================================================

ANPCCharacter::ANPCCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

    // Create dialogue component
    DialogueComp = CreateDefaultSubobject<UDialogueComponent>(TEXT("DialogueComponent"));

    // NPC characters don't need combat setup
    if (UCharacterMovementComponent* Movement = GetCharacterMovement())
    {
        Movement->bUseFlatBaseForFloorCheck = true;
    }

    // Set base mesh collision
    if (GetCapsuleComponent())
    {
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    }
}

void ANPCCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ANPCCharacter, NPCType);
    DOREPLIFETIME(ANPCCharacter, NPCState);
    DOREPLIFETIME(ANPCCharacter, ActiveQuests);
    DOREPLIFETIME(ANPCCharacter, CompletedQuests);
    DOREPLIFETIME(ANPCCharacter, AvailableQuests);
    DOREPLIFETIME(ANPCCharacter, Reputation);
}

void ANPCCharacter::BeginPlay()
{
    Super::BeginPlay();

    PatrolCenter = GetActorLocation();

    // Merchant and vendor NPCs start idle
    if (NPCType == ENPCType::Merchant || NPCType == ENPCType::Vendor)
    {
        SetNPCState(ENPCState::Idle);
    }
}

void ANPCCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!HasAuthority())
        return;

    // Update AI behavior based on state
    switch (NPCState)
    {
    case ENPCState::Patrolling:
    {
        // Simple patrol behavior
        FVector CurrentLocation = GetActorLocation();
        FVector ToCenter = PatrolCenter - CurrentLocation;
        float DistanceFromCenter = ToCenter.Size2D();

        if (DistanceFromCenter > PatrolRadius)
        {
            // Return to patrol center
            AddMovementInput(ToCenter.GetSafeNormal(), 1.f);
        }
        break;
    }
    case ENPCState::Alert:
        // NPC is alerted, investigating
        break;
    case ENPCState::Hostile:
        // Combat behavior
        break;
    default:
        break;
    }
}

void ANPCCharacter::SetNPCType(ENPCType NewType)
{
    if (!HasAuthority())
        return;

    NPCType = NewType;

    // Configure behavior based on type
    switch (NPCType)
    {
    case ENPCType::Guard:
        SetNPCState(ENPCState::Patrolling);
        bCanInteract = false;
        break;
    case ENPCType::Merchant:
    case ENPCType::Vendor:
        SetNPCState(ENPCState::Idle);
        bCanInteract = true;
        InteractionPrompt = FText::FromString(TEXT("Trade"));
        break;
    case ENPCType::QuestGiver:
        bCanInteract = true;
        InteractionPrompt = FText::FromString(TEXT("Quest"));
        break;
    case ENPCType::Civilian:
    case ENPCType::Informant:
        bCanInteract = true;
        InteractionPrompt = FText::FromString(TEXT("Talk"));
        break;
    default:
        break;
    }
}

void ANPCCharacter::SetNPCState(ENPCState NewState)
{
    if (!HasAuthority())
        return;

    ENPCState OldState = NPCState;
    NPCState = NewState;

    OnNPCStateChanged.Broadcast(OldState, NewState);

    // Handle state transitions
    if (NewState == ENPCState::Conversing)
    {
        // Stop movement during dialogue
        if (UCharacterMovementComponent* Movement = GetCharacterMovement())
        {
            Movement->StopMovementImmediately();
        }
    }
}

void ANPCCharacter::StartDialogue(AActor* Player)
{
    if (!bCanInteract)
        return;

    SetNPCState(ENPCState::Conversing);
    
    if (DialogueComp)
    {
        DialogueComp->StartDialogue(Player);
    }
}

void ANPCCharacter::Interact(AActor* Interactor)
{
    if (!CanInteract())
        return;

    // Guards may attack instead of talking
    if (NPCType == ENPCType::Guard)
    {
        // Check if player is hostile to this NPC's faction
        SetNPCState(ENPCState::Hostile);
        return;
    }

    // Start dialogue
    StartDialogue(Interactor);
}

bool ANPCCharacter::CanInteract() const
{
    return bCanInteract && NPCState != ENPCState::Conversing;
}

FText ANPCCharacter::GetInteractionPrompt() const
{
    if (!bCanInteract)
        return FText::GetEmpty();

    // Add quest indicator if has new quests
    if (NPCType == ENPCType::QuestGiver && AvailableQuests.Num() > 0)
    {
        return FText::FromString(TEXT("! Quest"));
    }

    return InteractionPrompt;
}

void ANPCCharacter::AssignQuest(const FName& QuestID)
{
    if (!HasAuthority())
        return;

    if (!ActiveQuests.Contains(QuestID))
    {
        ActiveQuests.Add(QuestID);
        OnQuestAssigned.Broadcast(QuestID);
    }
}

void ANPCCharacter::CompleteQuest(const FName& QuestID)
{
    if (!HasAuthority())
        return;

    ActiveQuests.Remove(QuestID);

    if (!CompletedQuests.Contains(QuestID))
    {
        CompletedQuests.Add(QuestID);
        OnQuestCompleted.Broadcast(QuestID);
    }
}

bool ANPCCharacter::HasQuest(const FName& QuestID) const
{
    return ActiveQuests.Contains(QuestID) || CompletedQuests.Contains(QuestID);
}

void ANPCCharacter::ModifyReputation(float Amount)
{
    if (!HasAuthority())
        return;

    Reputation = FMath::Clamp(Reputation + Amount, 0.f, 100.f);
    OnReputationChanged.Broadcast(Reputation);
}
