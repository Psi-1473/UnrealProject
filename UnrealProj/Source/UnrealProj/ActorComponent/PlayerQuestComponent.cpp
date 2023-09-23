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
	// �� ��
	// 1. Npc�� QuestComponent�� �����Ͽ� ���ǰ� ��ġ�ϴ� ����Ʈ �����͸� �����´�.
	FQuestData* Data = Npc->GetQuestComponent()->GetPossibleQuestDataByQuestIndex(QuestId);

	if (Data == nullptr)
		return;
	// 2. Npc�� QuestComponent�� �����Ͽ� ���� ���� ����Ʈ�� ������ ����Ʈ�� �ű��.
	Npc->GetQuestComponent()->PossibleToOngoing(Data);
	Npc->UpdateQuestMark();

	// 3. ���ο� UQuest Ŭ������ �����(��������) 1���� ������ ����Ʈ �����͸� ���� �ʱ�ȭ���ش�. 
	UQuest* NewQuest = CreateNewQuest(Data);
 
	// 4. 3���� ���� UQeust Ŭ������ OnGoingQuests�� �߰��Ѵ�.
	OnGoingQuests.Add(NewQuest);
	 
	// 5. �ش� ����Ʈ�� � Ÿ���̳Ŀ� ���� Hunt, Item, Investigate ����Ʈ�� �߰����ش�.

}

UQuest* UPlayerQuestComponent::CreateNewQuest(FQuestData* QuestData)
{
	UQuest* Quest = NewObject<UQuest>();
	Quest->BindQuest(QuestData);

	return Quest;
}



