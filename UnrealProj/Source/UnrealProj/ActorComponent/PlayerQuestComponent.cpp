// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerQuestComponent.h"
#include "../Creatures/Npc/Npc.h"
#include "QuestComponent.h"
#include "../MyGameInstance.h"
#include "../DataClass/Quest.h"
#include "../DEFINE.h"


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
	FQuestData* Data = Npc->GetQuestComponent()->GetPossibleQuestDataByQuestIndex(QuestId);

	if (Data == nullptr)
		return;

	UQuest* NewQuest = CreateNewQuest(Data);

	if (Data->QuestType == QUEST_NORMAL)
	{
		Npc->GetQuestComponent()->RemovePossibleQuest(QuestId);
		NewQuest->GetClearNpc()->GetQuestComponent()->AddCompletableQuest(NewQuest);
		CompletableQuests.Add(NewQuest);
		Npc->UpdateQuestMark();
	}
	else
	{
		Npc->GetQuestComponent()->RemovePossibleQuest(QuestId);
		Npc->GetQuestComponent()->AddOngoingQuest(NewQuest);
		Npc->UpdateQuestMark();
		OnGoingQuests.Add(NewQuest);

		// 퀘스트 타입에 따라
	}

	// 5. 해당 퀘스트가 어떤 타입이냐에 따라 Hunt, Item, Investigate 퀘스트에 추가해준다.
}

void UPlayerQuestComponent::ClearQuest(UQuest* Quest)
{
	UE_LOG(LogTemp, Warning, TEXT("Quest Clear"));
	Quest->GetClearNpc()->GetQuestComponent()->RemoveCompletableQuest(Quest);
	Quest->GetClearNpc()->UpdateQuestMark();
	CompletableQuests.Remove(Quest);
	// 플레이어의 완료 퀘스트 목록에 추가


	// 현재 퀘스트 로드 안되게 막기
	// 
	// 
	// 연계 퀘스트 해방
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	int NextNpcId = Quest->GetNextNpcId();
	int NextQuestId = Quest->GetNextQuestId();

	if (NextNpcId == 0 || NextQuestId == 0)
		return;
	GInstance->GetSingleQuestData(NextNpcId, NextQuestId)->CanLoad = true;
	GInstance->GetNpcList()[NextNpcId]->LoadPossibleQuestData();


}

void UPlayerQuestComponent::OnGoingToCompletable(UQuest* Quest)
{	
	OnGoingQuests.Remove(Quest);
	CompletableQuests.Add(Quest);
	Quest->GetStartNpc()->GetQuestComponent()->RemoveOngoingQuest(Quest);
	Quest->GetClearNpc()->GetQuestComponent()->AddCompletableQuest(Quest);

}

UQuest* UPlayerQuestComponent::CreateNewQuest(FQuestData* QuestData)
{
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	UQuest* Quest = NewObject<UQuest>();
	Quest->BindQuest(GInstance, QuestData);

	return Quest;
}



