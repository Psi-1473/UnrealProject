// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"
#include "../Creatures/Npc/Npc.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../MyGameInstance.h"
#include "../ActorComponent/QuestComponent.h"
#include "../ActorComponent/PlayerQuestComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Stat/PlayerStatComponent.h"

void UQuestManager::LoadNpcQuest(ANpc* Npc, AMyPlayer* Player)
{
	auto GInstance = Cast<UMyGameInstance>(Npc->GetGameInstance());

	UDataTable* Table = GInstance->GetQuestData(Npc->GetId());

	if (Table == nullptr)
		return;

	int TableCount = Table->GetRowNames().Num();
	UE_LOG(LogTemp, Warning, TEXT("LoadNpcQuest "));
	for (int i = 0; i < TableCount; i++)
	{
		FQuestData* QData = Table->FindRow<FQuestData>(*FString::FromInt(i + 1), TEXT(""));
		if (QData->CanLoad == false) continue; // 플레이어 레벨로 수정
		if (Player->GetStatComponent()->GetLevel() < QData->PossibleLevel) continue;
		// if 이미 불러온 퀘스트면 continue;


		UE_LOG(LogTemp, Warning, TEXT("Cand Load True : %d"), CompletedQuestList[Npc->GetId()].QuestIds.Find(QData->Id));

		if (CompletedQuestList[Npc->GetId()].QuestIds.Find(QData->Id) != INDEX_NONE)
			continue;

			Npc->GetQuestComponent()->LoadPossibleQuest(QData);
			UE_LOG(LogTemp, Warning, TEXT("QUEST NAME : %s"), *QData->Name);
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
