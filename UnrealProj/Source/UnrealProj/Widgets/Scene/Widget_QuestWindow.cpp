// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_QuestWindow.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "../../MyGameInstance.h"
#include "../../Managers/QuestManager.h"
#include "../../DataClass/Quest.h"
#include "../../Managers/UIManager.h"
#include "../Popup/Widget_QuestQuickInfo.h"

UWidget_QuestWindow::UWidget_QuestWindow(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> SA(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Popup/WBP_QuestQuickInfo.WBP_QuestQuickInfo_C'"));
	if (SA.Succeeded()) BP_Slot = SA.Class;
}

void UWidget_QuestWindow::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Minimization->OnClicked.AddDynamic(this, &UWidget_QuestWindow::MinimizationWindow);
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	GInstance->GetQuestMgr()->SetQuestWindow(this);

}

void UWidget_QuestWindow::MinimizationWindow()
{
	if (ListVisibility)
	{
		ListVisibility = false;
		BackGround_List->SetVisibility(ESlateVisibility::Hidden);
		ScrollBox_List->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ListVisibility = true;
		BackGround_List->SetVisibility(ESlateVisibility::Visible);
		ScrollBox_List->SetVisibility(ESlateVisibility::Visible);
	}
}

void UWidget_QuestWindow::AddQuest(UQuest* Data)
{
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	auto Widget = CreateWidget(GetWorld(), BP_Slot);
	auto Quick = Cast<UWidget_QuestQuickInfo>(Widget);

	ScrollBox_List->AddChild(Widget);
	// 화면에 띄우는 함수도 추가
	Quick->BindQuest(Data);
	Slots.Add(Quick);
	UE_LOG(LogTemp, Warning, TEXT("ADD Quest! %d"), Slots.Num());
}

void UWidget_QuestWindow::RemoveQuest(UQuest* Data)
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		UWidget_QuestQuickInfo* InfoWidget = Slots[i];

		UE_LOG(LogTemp, Warning, TEXT("Widget : %d, %d . Data : %d, %d"), InfoWidget->GetQuest()->GetNpcId(),
			InfoWidget->GetQuest()->GetQuestId(),
			Data->GetNpcId(),
			Data->GetQuestId());
		if (InfoWidget->GetQuest()->GetNpcId() == Data->GetNpcId() &&
			InfoWidget->GetQuest()->GetQuestId() == Data->GetQuestId())
		{
			UE_LOG(LogTemp, Warning, TEXT("RemoveQuest"));
			InfoWidget->RemoveFromParent();
			Slots.Remove(InfoWidget);
			return;
		}
	}
}
