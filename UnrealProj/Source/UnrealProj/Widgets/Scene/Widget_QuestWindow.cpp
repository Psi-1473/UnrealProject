// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_QuestWindow.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "../../MyGameInstance.h"
#include "../../Managers/QuestManager.h"
#include "../../Managers/UIManager.h"
#include "../Popup/Widget_QuestQuickInfo.h"

void UWidget_QuestWindow::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Minimization->OnClicked.AddDynamic(this, &UWidget_QuestWindow::MinimizationWindow);
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	GInstance->GetQuestMgr()->SetQuestWindow(this);

}

void UWidget_QuestWindow::MinimizationWindow()
{
	UE_LOG(LogTemp, Warning, TEXT("BTN CLICKED!"));

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
	auto Widget = GInstance->GetUIMgr()->PopupUI(GetWorld(), UIType::QuestQuickInfo);
	auto Quick = Cast<UWidget_QuestQuickInfo>(Widget);

	ScrollBox_List->AddChild(Widget);
	// 화면에 띄우는 함수도 추가
	Quick->BindQuest(Data);
	Slots.Add(Quick);
}

void UWidget_QuestWindow::RemoveQuest(UQuest* Data)
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		UWidget_QuestQuickInfo* InfoWidget = Slots[i];
		if (InfoWidget->GetQuest() == Data)
		{
			Slots.Remove(InfoWidget);
			return;
		}
	}
}
