// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"
#include "../Creatures/Npc/Npc.h"
#include "../MyGameInstance.h"
#include "../ActorComponent/QuestComponent.h"

void UQuestManager::LoadNpcQuest(ANpc* Npc)
{
	auto GInstance = Cast<UMyGameInstance>(Npc->GetGameInstance());

	UDataTable* Table = GInstance->GetQuestData(Npc->GetId());

	if (Table == nullptr)
		return;

	int TableCount = Table->GetRowNames().Num();

	for (int i = 0; i < TableCount; i++)
	{
		FQuestData* QData = Table->FindRow<FQuestData>(*FString::FromInt(i + 1), TEXT(""));
		if (QData->CanLoad == true)
		{
			Npc->GetQuestComponent()->LoadPossibleQuest(QData);
			UE_LOG(LogTemp, Warning, TEXT("QUEST NAME : %s"), *QData->Name);
		}
	}



}
