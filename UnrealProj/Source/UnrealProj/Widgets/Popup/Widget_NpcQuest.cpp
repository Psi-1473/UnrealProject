// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_NpcQuest.h"
#include "../../ActorComponent/QuestComponent.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Widget_NpcQuestSlot.h"

UWidget_NpcQuest::UWidget_NpcQuest(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> SLOT(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Slots/WBP_NpcQuestSlot.WBP_NpcQuestSlot_C'"));
	if (SLOT.Succeeded()) BP_Slot = SLOT.Class;
}

void UWidget_NpcQuest::BindAndCreateSlot(UQuestComponent* QuestComp)
{
	QuestComponent = QuestComp;
	int Cnt = QuestComponent->GetPossibleQuestNum();
	for (int i = 0; i < Cnt; i++)
	{
		UUserWidget* NewSlot = CreateWidget(GetWorld(), BP_Slot);
		ScrollBox_QuestList->AddChild(NewSlot);
		NewSlot->SetPadding(FMargin(20.f, 10.f, 10.f, 0.f));
		UWidget_NpcQuestSlot* QSlot = Cast<UWidget_NpcQuestSlot>(NewSlot);
		if (QSlot == nullptr)
			return;
		QSlot->Init(this, QuestComponent->GetPossibleQuestData(i));
	}

}

void UWidget_NpcQuest::UpdateInfo(FQuestData Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Update QuestInfo"));
	SelectedQuestId = Data.Id;
	Text_QuestTitle->SetText(FText::FromString(Data.Name));
	Text_QuestInfo->SetText(FText::FromString(Data.Explanation));
}
