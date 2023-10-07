// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerQuestComponent.h"
#include "../Creatures/Npc/Npc.h"
#include "QuestComponent.h"
#include "../MyGameInstance.h"
#include "../Managers/QuestManager.h"
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
		NewQuest->GetClearNpc()->UpdateQuestMark();
	}
	else
	{
		Npc->GetQuestComponent()->RemovePossibleQuest(QuestId);
		Npc->GetQuestComponent()->AddOngoingQuest(NewQuest);
		Npc->UpdateQuestMark();
		OnGoingQuests.Add(NewQuest);

		// 퀘스트 타입에 따라

		switch (Data->QuestType)
		{
		case QUEST_HUNT:
			HuntQuests.Add(NewQuest);
			break;
		case QUEST_ITEM:
			ItemQuests.Add(NewQuest);
			break;
		case QUEST_ETC:
			EtcQuests.Add(NewQuest);
			break;
		case QUEST_INVESTIGATE:
			InvestigateQuests.Add(NewQuest);
			break;
		default:
			break;
		}
	}

	// 5. 해당 퀘스트가 어떤 타입이냐에 따라 Hunt, Item, Investigate 퀘스트에 추가해준다.
}

void UPlayerQuestComponent::CheckQuest(int QuestType, int TargetId, int TargetType)
{
	switch (QuestType)
	{
	case QUEST_HUNT:
		CheckHuntQuest(TargetId);
		break;
	case QUEST_ITEM:
		CheckItemQuest(TargetType, TargetId);
		break;
	case QUEST_ETC:
		UE_LOG(LogTemp, Warning, TEXT("Take ETC"));
		CheckETCQuest(TargetId);
		break;
	case QUEST_INVESTIGATE:
		CheckInvestigateQuest(TargetId);
		break;
	default:
		break;
	}
}

void UPlayerQuestComponent::CheckHuntQuest(int TargetId)
{
	TArray<UQuest*> QuestsToRemove;
	for (int i = 0; i < HuntQuests.Num(); i++)
	{
		UQuest* Quest = HuntQuests[i];
		if (Quest->GetTargetId() == TargetId)
		{
			Quest->AddNowNum();
			if (Quest->GetTargetNowNum() < Quest->GetTargetMaxNum())
				continue;

			QuestsToRemove.Add(Quest);
			OnGoingToCompletable(Quest);
		}
	}

	for (int i = 0; i < QuestsToRemove.Num(); i++)
	{
		UQuest* Quest = QuestsToRemove[i];
		HuntQuests.RemoveSingle(Quest);
	}
}

void UPlayerQuestComponent::CheckItemQuest(int TargetType, int TargetId)
{
	// Temp
	TArray<UQuest*> QuestsToRemove;
	for (int i = 0; i < ItemQuests.Num(); i++)
	{
		UQuest* Quest = ItemQuests[i];
		if (TargetType != Quest->GetTargetType())
			continue;
		if (Quest->GetTargetId() == TargetId)
		{
			Quest->AddNowNum();
			if (Quest->GetTargetNowNum() < Quest->GetTargetMaxNum())
				continue;

			QuestsToRemove.Add(Quest);
			OnGoingToCompletable(Quest);
		}
	}

	for (int i = 0; i < QuestsToRemove.Num(); i++)
	{
		UQuest* Quest = QuestsToRemove[i];
		ItemQuests.RemoveSingle(Quest);
	}

	// 아이템 바인딩해서 설계 새로
}

void UPlayerQuestComponent::CheckInvestigateQuest(int TargetId)
{
	TArray<UQuest*> QuestsToRemove;
	for (int i = 0; i < InvestigateQuests.Num(); i++)
	{
		UQuest* Quest = InvestigateQuests[i];
		if (Quest->GetTargetId() == TargetId)
		{
			Quest->AddNowNum();
			if (Quest->GetTargetNowNum() < Quest->GetTargetMaxNum())
				continue;

			QuestsToRemove.Add(Quest);
			OnGoingToCompletable(Quest);
		}
	}

	for (int i = 0; i < QuestsToRemove.Num(); i++)
	{
		UQuest* Quest = QuestsToRemove[i];
		InvestigateQuests.RemoveSingle(Quest);
	}
}

void UPlayerQuestComponent::CheckETCQuest(int EtcType)
{
	// ETC 퀘스트는 특정 행위가 다 다를거고 그 행위가 한 번만 이루어지면 클리어 되게 할 것이기 때문에
	// for문을 돌다가 조건에 부합하는 퀘스트 발견시 클리어, Remove하고 바로 return 해도 무관.
	// 바로 return 하는 이유눈 for문이 EtcQuests.Num만큼 도는데 Remove를 하고 계속 for문을 돌면
	// EtcQuest.Num이랑 실제 돌아야하는 데이터 수가 달라짐

	UE_LOG(LogTemp, Warning, TEXT("Check ETC"));
	for (int i = 0; i < EtcQuests.Num(); i++)
	{
		UQuest* Quest = EtcQuests[i];
		if (Quest->GetTargetId() == EtcType)
		{
			OnGoingToCompletable(Quest);
			EtcQuests.RemoveSingle(Quest);
			return;
		}
	}
}

void UPlayerQuestComponent::ClearQuest(UQuest* Quest)
{
	UE_LOG(LogTemp, Warning, TEXT("Quest Clear"));
	Quest->GetClearNpc()->GetQuestComponent()->RemoveCompletableQuest(Quest);
	Quest->GetClearNpc()->UpdateQuestMark();
	CompletableQuests.Remove(Quest);

	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());

	GInstance->GetQuestMgr()->AddToCompletedList(Quest->GetNpcId(), Quest->GetQuestId());

	int NextNpcId = Quest->GetNextNpcId();
	int NextQuestId = Quest->GetNextQuestId();

	GInstance->GetQuestMgr()->RemoveQuickQuest(Quest);
	BindedQuest.Remove(Quest);

	if (NextNpcId == 0 || NextQuestId == 0)
		return;
	GInstance->GetQuestMgr()->LoadNpcQuest(Quest->GetNextNpc(), NextQuestId);
	Quest->GetNextNpc()->UpdateQuestMark();
	//Quest->GetClearNpc()->GetQuestComponent()->DecreaseMainCompletableNumber();
	Quest->GetClearNpc()->UpdateQuestMark();
}

void UPlayerQuestComponent::OnGoingToCompletable(UQuest* Quest)
{	
	OnGoingQuests.Remove(Quest);
	CompletableQuests.Add(Quest);
	Quest->GetStartNpc()->GetQuestComponent()->RemoveOngoingQuest(Quest);
	Quest->GetClearNpc()->GetQuestComponent()->AddCompletableQuest(Quest);

	Quest->GetStartNpc()->UpdateQuestMark();
	Quest->GetClearNpc()->UpdateQuestMark();

}

// 이미 등록된 퀘스트 = false, 새로 등록 = true 리턴
bool UPlayerQuestComponent::AdddToBindedQuest(UQuest* Quest)
{
	if (BindedQuest.Find(Quest) != INDEX_NONE)
		return false;

	BindedQuest.Add(Quest);
	return true;
}

UQuest* UPlayerQuestComponent::CreateNewQuest(FQuestData* QuestData)
{
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	UQuest* Quest = NewObject<UQuest>();
	Quest->BindQuest(GInstance, QuestData);

	return Quest;
}



