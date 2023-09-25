// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_QuestInfo.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../../DataClass/Quest.h"
#include "Widget_Quest.h"

void UWidget_QuestInfo::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidget_QuestInfo::SetQuestInfo(TWeakObjectPtr<UWidget_Quest> Widget, UQuest* Data)
{
	QuestWidget = Widget;
	Text_QuestTitle->SetText(FText::FromString(*Data->GetQuestName()));
	Text_QuestInfo->SetText(FText::FromString(*Data->GetQuestExplanation()));

}

void UWidget_QuestInfo::ClickExitBtn()
{
	QuestWidget->SetOffInfoWidget();
}
