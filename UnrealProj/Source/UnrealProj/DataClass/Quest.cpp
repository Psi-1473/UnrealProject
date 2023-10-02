// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"
#include "../MyGameInstance.h"
#include "../DEFINE.h"

FString UQuest::GetTargetName(int QType, int TId, int TType)
{
	FString ReturnName;

	if (QType == (int)QUEST_HUNT)
	{
		ReturnName = GameInstance->GetMonsterStat(TargetId)->Name;
	}
	else if (QType == (int)QUEST_ITEM)
	{
		// TargetType에 따라 분류
	}

	return ReturnName;
}

void UQuest::BindQuest(UMyGameInstance* GInstance, FQuestData* QuestData)
{
	// 바인드 퀘스트
	// Type
	GameInstance = GInstance;
	NpcId = QuestData->QuestNpcId;
	QuestId = QuestData->Id;
	Name = QuestData->Name;
	Explanation = QuestData->Explanation;
	TargetId = QuestData->TargetId;
	TargetType = QuestData->TargetType;
	TargetMaxNum = QuestData->TargetNum;
	TargetNowNum = 0;
	Type = QuestData->QuestType;
	QuestLevel = QuestData->QuestLevel;
	NextNpcId = QuestData->NextQuestNpcId;
	NextQuestId = QuestData->NextQuestId;
	Summary = QuestData->Summary;

	StartNpc = GInstance->GetNpcList()[NpcId];
	ClearNpc = GInstance->GetNpcList()[QuestData->ClearNpcId];
	NextNpc = GInstance->GetNpcList()[QuestData->NextQuestNpcId];




}
