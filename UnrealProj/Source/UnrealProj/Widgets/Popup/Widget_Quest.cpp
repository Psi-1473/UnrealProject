// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Quest.h"
#include "../../ActorComponent/PlayerQuestComponent.h"
#include "../../DataClass/Quest.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Widget_QuestSlot.h"
#include "Widget_QuestInfo.h"
#include "../../MyGameInstance.h"
#include "../../Managers/UIManager.h"

UWidget_Quest::UWidget_Quest(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> SLOT(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Slots/WBP_QuestSlot.WBP_QuestSlot_C'"));
	if (SLOT.Succeeded()) BP_Slot = SLOT.Class;
}

void UWidget_Quest::NativeConstruct()
{
	Super::NativeConstruct();
	SetOffInfoWidget();

	Btn_Exit->OnClicked.AddDynamic(this, &UWidget_Quest::CloseUI);
	Btn_OnGoing->OnClicked.AddDynamic(this, &UWidget_Quest::SetListToOnGoingQuests);
	Btn_Complete->OnClicked.AddDynamic(this, &UWidget_Quest::SetListToCompleteQuests);
	// 버튼 바인딩
}

void UWidget_Quest::CreateSlot(UPlayerQuestComponent* QuestComponent)
{
	for (int i = 0; i < QuestComponent->GetCompletableQuests().Num(); i++)
	{
		UUserWidget* NewSlot = CreateWidget(GetWorld(), BP_Slot);
		ScrollBox_QuestList->AddChild(NewSlot);
		UWidget_QuestSlot* QSlot = Cast<UWidget_QuestSlot>(NewSlot);
		QSlot->SetCompletable(true);
		QSlot->SetInfo(this, QuestComponent->GetCompletableQuests()[i]);
	}

	for (int i = 0; i < QuestComponent->GetOnGoingQuests().Num(); i++)
	{
		UUserWidget* NewSlot = CreateWidget(GetWorld(), BP_Slot);
		ScrollBox_QuestList->AddChild(NewSlot);
		UWidget_QuestSlot* QSlot = Cast<UWidget_QuestSlot>(NewSlot);
		QSlot->SetCompletable(false);
		QSlot->SetInfo(this, QuestComponent->GetOnGoingQuests()[i]);
	}
}

void UWidget_Quest::UpdateQuestInfo(UQuest* QData)
{
	if (WBP_QuestInfo->GetVisibility() != ESlateVisibility::Visible)
		WBP_QuestInfo->SetVisibility(ESlateVisibility::Visible);

	WBP_QuestInfo->SetQuestInfo(this, QData);
}

void UWidget_Quest::SetOffInfoWidget()
{
	WBP_QuestInfo->SetVisibility(ESlateVisibility::Hidden);
}

void UWidget_Quest::SetListToOnGoingQuests()
{
}

void UWidget_Quest::SetListToCompleteQuests()
{
}

void UWidget_Quest::CloseUI()
{
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	GInstance->GetUIMgr()->CloseUI((int)UIType::Quest);
}
