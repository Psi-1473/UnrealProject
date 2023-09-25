// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_QuestSlot.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../../DataClass/Quest.h"
#include "../../MyGameInstance.h"
#include "../../Managers/UIManager.h"
#include "Widget_QuestInfo.h"
#include "Widget_Quest.h"

void UWidget_QuestSlot::NativeConstruct()
{
	Super::NativeConstruct();
	// 버튼 바인딩
	Btn_QuestName->OnClicked.AddDynamic(this, &UWidget_QuestSlot::PopupQuestInfoUI);
}

void UWidget_QuestSlot::SetInfo(TWeakObjectPtr<UWidget_Quest> Widget, UQuest* QuestData)
{
	QuestWidget = Widget;
	Quest = QuestData;
	Text_QuestName->SetText(FText::FromString(*QuestData->GetQuestName()));
}

void UWidget_QuestSlot::PopupQuestInfoUI()
{
	QuestWidget->UpdateQuestInfo(Quest);
}
