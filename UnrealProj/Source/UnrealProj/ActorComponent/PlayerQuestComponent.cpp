// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerQuestComponent.h"
#include "../Creatures/Npc/Npc.h"
#include "QuestComponent.h"
#include "../MyGameInstance.h"
#include "../DataClass/Quest.h"

UPlayerQuestComponent::UPlayerQuestComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}


void UPlayerQuestComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UPlayerQuestComponent::TakeNewQuest(ANpc* Npc, int32 QuestId)
{
	// 할 일
	// 1. Npc의 QuestComponent에 접근하여 조건과 일치하는 퀘스트 데이터를 가져온다.
	FQuestData* Data = Npc->GetQuestComponent()->GetPossibleQuestDataByQuestIndex(QuestId);

	if (Data == nullptr)
		return;
	// 2. Npc의 QuestComponent에 접근하여 시작 가능 퀘스트를 진행중 퀘스트로 옮긴다.
	Npc->GetQuestComponent()->PossibleToOngoing(Data);
	Npc->UpdateQuestMark();

	// 3. 새로운 UQuest 클래스를 만들고(동적으로) 1에서 가져온 퀘스트 데이터를 통해 초기화해준다. 
	UQuest* NewQuest = CreateNewQuest(Data);
 
	// 4. 3에서 만든 UQeust 클래스를 OnGoingQuests에 추가한다.
	OnGoingQuests.Add(NewQuest);
	 
	// 5. 해당 퀘스트가 어떤 타입이냐에 따라 Hunt, Item, Investigate 퀘스트에 추가해준다.

}

UQuest* UPlayerQuestComponent::CreateNewQuest(FQuestData* QuestData)
{
	UQuest* Quest = NewObject<UQuest>();
	Quest->BindQuest(QuestData);

	return Quest;
}



