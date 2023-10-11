// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestComponent.h"
#include "../MyGameInstance.h"
#include "../Creatures/Npc/Npc.h"
#include "../DEFINE.h"
#include "../DataClass/Quest.h"

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	MainPossibleNumber = 0;
	MainCompletableNumber = 0;
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
	return GInstance->GetSingleQuestData(Npc->GetId(), QuestId);
}

void UQuestComponent::LoadPossibleQuest(FQuestData* Data)
{	
	if(PossibleQuests.Find(Data->Id) != INDEX_NONE)
		return;

	if(IsQuestInOnGoing(Data->Id))
		return;

	if (IsQuestInCompletable(Data->Id))
		return;

	UE_LOG(LogTemp, Warning, TEXT("QUEST LOADED!"));
	PossibleQuests.Add(Data->Id);

	if (Data->QuestLevel == (int)QuestLevel::MAIN)
		MainPossibleNumber++;
}

void UQuestComponent::RemovePossibleQuest(int QuestId)
{
	PossibleQuests.Remove(QuestId);
	auto Npc = Cast<ANpc>(GetOwner());
	auto GInstance = Cast<UMyGameInstance>(GetOwner()->GetGameInstance());
	FQuestData* Data = GInstance->GetSingleQuestData(Npc->GetId(), QuestId);

	if (Data->QuestLevel == (int)QuestLevel::MAIN)
		MainPossibleNumber--;
}

void UQuestComponent::RemoveOngoingQuest(UQuest* Quest)
{
	OngoingQuests.Remove(Quest);
}

void UQuestComponent::RemoveCompletableQuest(UQuest* Quest)
{
	CompletableQuests.Remove(Quest);
	if (Quest->GetQuestLevel() == (int)QuestLevel::MAIN)
		MainCompletableNumber--;
}

void UQuestComponent::AddPossibleQuest(int QuestId)
{
	PossibleQuests.Add(QuestId);
	auto Npc = Cast<ANpc>(GetOwner());
	auto GInstance = Cast<UMyGameInstance>(GetOwner()->GetGameInstance());
	FQuestData* Data = GInstance->GetSingleQuestData(Npc->GetId(), QuestId);

	if(Data->QuestLevel == (int)QuestLevel::MAIN)
		MainPossibleNumber++;
}

void UQuestComponent::AddOngoingQuest(UQuest* Quest)
{
	OngoingQuests.Add(Quest);
}

void UQuestComponent::AddCompletableQuest(UQuest* Quest)
{
	CompletableQuests.Add(Quest);

	if (Quest->GetQuestLevel() == (int)QuestLevel::MAIN)
		MainCompletableNumber++;
}

bool UQuestComponent::IsQuestInOnGoing(int Id)
{
	for (int i = 0; i < OngoingQuests.Num(); i++)
	{
		if(OngoingQuests[i]->GetQuestId() == Id)
			return true;
	}
	return false;
}

bool UQuestComponent::IsQuestInCompletable(int Id)
{
	for (int i = 0; i < CompletableQuests.Num(); i++)
	{
		if (CompletableQuests[i]->GetQuestId() == Id)
			return true;
	}
	return false;
}
