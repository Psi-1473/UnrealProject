// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"
#include "../MyGameInstance.h"

void UQuest::BindQuest(UMyGameInstance* GInstance, FQuestData* QuestData)
{
	// 바인드 퀘스트
	// Type

	NpcId = QuestData->QuestNpcId;
	QuestId = QuestData->Id;
	Name = QuestData->Name;
	Explanation = QuestData->Explanation;
	TargetId = QuestData->TargetId;
	TargetMaxNum = QuestData->TargetNum;
	TargetNowNum = 0;
	Type = QuestData->QuestType;
	QuestLevel = QuestData->QuestLevel;
	NextNpcId = QuestData->NextQuestNpcId;
	NextQuestId = QuestData->NextQuestId;

	StartNpc = GInstance->GetNpcList()[NpcId];
	ClearNpc = GInstance->GetNpcList()[QuestData->ClearNpcId];




}
