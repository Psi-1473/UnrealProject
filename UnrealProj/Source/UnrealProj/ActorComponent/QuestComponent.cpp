// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestComponent.h"
#include "../MyGameInstance.h"
#include "../Creatures/Npc/Npc.h"

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	
}


// Called when the game starts
void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

FQuestData* UQuestComponent::GetQuestInfoByQuestId(int QuestId)
{
	auto Npc = Cast<ANpc>(GetOwner());
	auto GInstance = Cast<UMyGameInstance>(GetOwner()->GetGameInstance());

	FQuestData* Data = GInstance->GetSingleQuestData(Npc->GetId(), QuestId);
	return Data;
}

FQuestData* UQuestComponent::GetPossibleQuestDataByQuestIndex(int Index)
{
	int ListIndex = PossibleQuests.Find(Index);
	if (ListIndex == INDEX_NONE)
		return nullptr;

	FQuestData* Data = GetPossibleQuestData(ListIndex);
	return Data;
}

FQuestData* UQuestComponent::GetPossibleQuestData(int PossibleListIndex)
{
	int QuestId = PossibleQuests[PossibleListIndex];
	auto Npc = Cast<ANpc>(GetOwner());
	auto GInstance = Cast<UMyGameInstance>(GetOwner()->GetGameInstance());
	GInstance->GetSingleQuestData(Npc->GetId(), QuestId);
	return GInstance->GetSingleQuestData(Npc->GetId(), QuestId);
}

void UQuestComponent::LoadPossibleQuest(FQuestData* Data)
{
	UE_LOG(LogTemp, Warning, TEXT("QUEST LOADED!"));
	PossibleQuests.Add(Data->Id);
}