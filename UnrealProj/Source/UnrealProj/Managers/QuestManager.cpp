// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"
#include "../Creatures/Npc/Npc.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../MyGameInstance.h"
#include "../ActorComponent/QuestComponent.h"
#include "../ActorComponent/PlayerQuestComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Stat/PlayerStatComponent.h"
#include "../DataClass/Quest.h"
#include "../Widgets/Scene/Widget_QuestWindow.h"

void UQuestManager::LoadNpcQuest(ANpc* Npc, AMyPlayer* Player)
{
	auto GInstance = Cast<UMyGameInstance>(Npc->GetGameInstance());

	UDataTable* Table = GInstance->GetQuestData(Npc->GetId());

	if (Table == nullptr)
		return;

	int TableCount = Table->GetRowNames().Num();
	for (int i = 0; i < TableCount; i++)
	{
		FQuestData* QData = Table->FindRow<FQuestData>(*FString::FromInt(i + 1), TEXT(""));

		if(QData->CanLoad == false) continue;
		if(Player->GetStatComponent()->GetLevel() < QData->PossibleLevel) continue;
		if(CompletedQuestList[Npc->GetId()].QuestIds.Find(QData->Id) != INDEX_NONE) continue;
		if(Npc->GetQuestComponent()->IsQuestInOnGoing(QData->Id)) continue;
		if(GInstance->GetNpcList()[QData->ClearNpcId]->GetQuestComponent()->IsQuestInCompletable(QData->Id)) continue;
		
		Npc->GetQuestComponent()->LoadPossibleQuest(QData);
	}
}

void UQuestManager::LoadNpcQuest(ANpc* Npc, int QuestId)
{
	auto GInstance = Cast<UMyGameInstance>(Npc->GetGameInstance());
	UDataTable* Table = GInstance->GetQuestData(Npc->GetId());
	FQuestData* QData = Table->FindRow<FQuestData>(*FString::FromInt(QuestId), TEXT(""));
	Npc->GetQuestComponent()->LoadPossibleQuest(QData);
}

void UQuestManager::LoadNpcQuestByLevelUp(AMyPlayer* Player)
{
	auto GInstance = Cast<UMyGameInstance>(Player->GetGameInstance());

	for (int i = 1; i < GInstance->GetNpcList().Num(); i++)
	{
		ANpc* Npc = GInstance->GetNpcList()[i];
		LoadNpcQuest(Npc, Player);
		Npc->UpdateQuestMark();
	}
}

void UQuestManager::CheckQuestTarget(int QuestType, int TargetId, TWeakObjectPtr<AMyPlayer> Player, int TargetType)
{
	Player->GetQuestComponent()->CheckQuest(QuestType, TargetId, TargetType);
}

void UQuestManager::InitCompletedList(int NpcNum)
{
	CompletedQuestList.Init(FQuestList(), NpcNum);
	UE_LOG(LogTemp, Warning, TEXT("INIT COMPLETED LIST ! : %d"), NpcNum);
}

void UQuestManager::AddToCompletedList(int NpcId, int QuestId)
{
	CompletedQuestList[NpcId].QuestIds.Add(QuestId);
}

void UQuestManager::BindQuickWindow(AMyPlayer* Player, UQuest* Quest)
{
	if(QuestQuickWindow == nullptr)
		return;

	// 0. Quest가 이미 등록되어 있는지 확인
	
	// 1. 플레이어의 BindQuest 리스트에 퀘스트 추가
	
	if (Player->GetQuestComponent()->AdddToBindedQuest(Quest))
	{
		// 2. 위젯 추가
		QuestQuickWindow->AddQuest(Quest);
	}
}

void UQuestManager::RemoveQuickQuest(UQuest* Quest)
{
	if (QuestQuickWindow == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("QuestWindow Null"));
		return;
	}

		
	QuestQuickWindow->RemoveQuest(Quest);
}
