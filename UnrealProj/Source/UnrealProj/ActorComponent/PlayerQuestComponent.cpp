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

		// ����Ʈ Ÿ�Կ� ����

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

	// 5. �ش� ����Ʈ�� � Ÿ���̳Ŀ� ���� Hunt, Item, Investigate ����Ʈ�� �߰����ش�.
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

	// ������ ���ε��ؼ� ���� ����
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
	// ETC ����Ʈ�� Ư�� ������ �� �ٸ��Ű� �� ������ �� ���� �̷������ Ŭ���� �ǰ� �� ���̱� ������
	// for���� ���ٰ� ���ǿ� �����ϴ� ����Ʈ �߽߰� Ŭ����, Remove�ϰ� �ٷ� return �ص� ����.
	// �ٷ� return �ϴ� ������ for���� EtcQuests.Num��ŭ ���µ� Remove�� �ϰ� ��� for���� ����
	// EtcQuest.Num�̶� ���� ���ƾ��ϴ� ������ ���� �޶���

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

// �̹� ��ϵ� ����Ʈ = false, ���� ��� = true ����
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



