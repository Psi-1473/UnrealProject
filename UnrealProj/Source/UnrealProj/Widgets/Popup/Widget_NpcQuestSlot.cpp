// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_NpcQuestSlot.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Widget_NpcQuest.h"

void UWidget_NpcQuestSlot::Init(UWidget_NpcQuest* QWidget, FQuestData* QData)
{
	QuestWidget = QWidget;
	QuestData = *QData;

	Text_QuestName->SetText(FText::FromString(QuestData.Name));
}
