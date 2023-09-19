// Fill out your copyright notice in the Description page of Project Settings.


#include "ScriptManager.h"
#include "Kismet/GameplayStatics.h"
#include "../MyGameInstance.h"

FString UScriptManager::GetQuestScript(int NpcId, int QuestId, int Page)
{
	FString Line = GInstance->GetQuestScript(NpcId, QuestId, Page);
	return FString();
}
