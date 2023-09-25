// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_NpcInfo.h"
#include "../../Creatures/Npc/Npc.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "../../ActorComponent/QuestComponent.h"

void UWidget_NpcInfo::BindNpc(ANpc* NpcValue)
{
	Npc = NpcValue;
	Text_Name->SetText(FText::FromString(NpcValue->GetNpcName()));
	UE_LOG(LogTemp, Warning, TEXT("Npc Info Bind"));
}

void UWidget_NpcInfo::UpdateQuestMark()
{
	int QuestNum = Npc->GetQuestComponent()->GetPossibleQuestNum();
	if (QuestNum > 0)
	{
		Img_QuestMark->SetVisibility(ESlateVisibility::Visible);
		// 퀘스트 마크 띄우기
	}
	else
	{
		Img_QuestMark->SetVisibility(ESlateVisibility::Hidden);
		// 퀘스트 마크 지우기

	}
}
