// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_QuestQuickInfo.h"
#include "Components/TextBlock.h"
#include "../../DataClass/Quest.h"

void UWidget_QuestQuickInfo::BindQuest(UQuest* Data)
{
	Quest = Data;
	Text_Title->SetText(FText::FromString(*Quest->GetQuestName()));
	Text_MissionObject->SetText(FText::FromString(*Quest->GetSummary()));

	if (Quest->GetQuestType() == QUEST_NORMAL)
	{
		Text_NowNum->SetText(FText::FromString(TEXT("")));
		Text_MaxNum->SetText(FText::FromString(TEXT("")));
	}
	else
	{
		Text_NowNum->SetText(FText::FromString(FString::FromInt(Quest->GetTargetNowNum())));
		Text_MaxNum->SetText(FText::FromString(FString::FromInt(Quest->GetTargetMaxNum())));
	}

	Quest->TargetNumChanged.AddUObject(this, &UWidget_QuestQuickInfo::RefreshNumber);
}

void UWidget_QuestQuickInfo::RefreshNumber()
{
	Text_NowNum->SetText(FText::FromString(FString::FromInt(Quest->GetTargetNowNum())));
}
