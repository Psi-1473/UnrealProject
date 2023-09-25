// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_NpcQuest.h"
#include "../../ActorComponent/QuestComponent.h"
#include "../../ActorComponent/PlayerQuestComponent.h"
#include "../../Creatures/Npc/Npc.h"
#include "Widget_LineScript.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Widget_NpcQuestSlot.h"
#include "Kismet/GameplayStatics.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Creatures/Npc/Npc.h"
#include "../../MyGameInstance.h"
#include "../../Managers/UIManager.h"
#include "../../DEFINE.h"

UWidget_NpcQuest::UWidget_NpcQuest(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> SLOT(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Slots/WBP_NpcQuestSlot.WBP_NpcQuestSlot_C'"));
	if (SLOT.Succeeded()) BP_Slot = SLOT.Class;

	
}

void UWidget_NpcQuest::NativeConstruct()
{
	Super::NativeConstruct();
}


void UWidget_NpcQuest::BindAndCreateSlot(TWeakObjectPtr<class ANpc> Npc)
{
	QuestComponent = Npc->GetQuestComponent();
	OwnerNpc = Npc;
	int Cnt = QuestComponent->GetPossibleQuestNum();
	for (int i = 0; i < Cnt; i++)
	{
		UUserWidget* NewSlot = CreateWidget(GetWorld(), BP_Slot);
		ScrollBox_QuestList->AddChild(NewSlot);
		NewSlot->SetPadding(FMargin(20.f, 10.f, 10.f, 0.f));
		UWidget_NpcQuestSlot* QSlot = Cast<UWidget_NpcQuestSlot>(NewSlot);
		QSlot->Init(Npc, QuestComponent->GetPossibleQuestData(i));
		Slots.Add(NewSlot);
	}
}

