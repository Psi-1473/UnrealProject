// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_QuestInfo.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../../DataClass/Quest.h"
#include "Widget_Quest.h"
#include "../../DEFINE.h"

void UWidget_QuestInfo::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidget_QuestInfo::SetQuestInfo(TWeakObjectPtr<UWidget_Quest> Widget, UQuest* Data)
{
	QuestWidget = Widget;
	Text_QuestTitle->SetText(FText::FromString(*Data->GetQuestName()));
	Text_QuestInfo->SetText(FText::FromString(*Data->GetQuestExplanation()));
	if (Data->GetQuestType() == QUEST_NORMAL)
	{
		Text_TargetMaxNum->SetText(FText::FromString(TEXT("")));
		Text_TargetNowNum->SetText(FText::FromString(TEXT("")));
		Text_TargetName->SetText(FText::FromString(TEXT("")));
	}
	else
	{
		Text_TargetMaxNum->SetText(FText::FromString(TEXT(" / ") + FString::FromInt(Data->GetTargetMaxNum())));
		Text_TargetNowNum->SetText(FText::FromString(FString::FromInt(Data->GetTargetNowNum())));
		Text_TargetName->SetText(FText::FromString(Data->GetTargetName(Data->GetQuestType(), Data->GetTargetId())));
	}

}

void UWidget_QuestInfo::ClickExitBtn()
{
	QuestWidget->SetOffInfoWidget();
}
