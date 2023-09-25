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
	Btn_Okay->OnClicked.AddDynamic(this, &UWidget_NpcQuest::TakeQuest);
}

void UWidget_NpcQuest::TakeQuest()
{
	if (SelectedQuestId == -1)
		return;

	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);

	auto GInstance = Cast<UMyGameInstance>(MyPlayer->GetGameInstance());
	auto Script = GInstance->GetUIMgr()->PopupUI(GetWorld(), UIType::LineScript);
	auto ScriptUI = Cast<UWidget_LineScript>(Script);
	ScriptUI->BindScript(GInstance->GetQuestScript(OwnerNpc->GetId(), SelectedQuestId), OwnerNpc->GetName());

	MyPlayer->GetQuestComponent()->TakeNewQuest(Cast<ANpc>(OwnerNpc), SelectedQuestId);
	UpdateSlot();
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

		Slots.Add(NewSlot);
	}

}

void UWidget_NpcQuest::UpdateSlot()
{
	for (int i = 0; i < Slots.Num(); i++)
		Slots[i]->RemoveFromViewport();

	Slots.Empty();
	BindAndCreateSlot(Cast<UQuestComponent>(QuestComponent));
	Text_QuestTitle->SetText(FText::FromString(TEXT("")));
	Text_QuestInfo->SetText(FText::FromString(TEXT("")));
}

void UWidget_NpcQuest::UpdateInfo(FQuestData Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Update QuestInfo"));
	SelectedQuestId = Data.Id;
	Text_QuestTitle->SetText(FText::FromString(Data.Name));
	Text_QuestInfo->SetText(FText::FromString(Data.Explanation));
}
