// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_QuestInfo.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../../DataClass/Quest.h"
#include "Widget_Quest.h"
#include "../../MyGameInstance.h"
#include "../../Managers/QuestManager.h"
#include "../../DEFINE.h"
#include "Kismet/GameplayStatics.h"
#include "../../Creatures/Player/MyPlayer.h"

void UWidget_QuestInfo::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_QuickSlot->OnClicked.AddDynamic(this, &UWidget_QuestInfo::RegisterQuickQuest);
	Btn_Exit->OnClicked.AddDynamic(this, &UWidget_QuestInfo::ClickExitBtn);
}

void UWidget_QuestInfo::SetQuestInfo(TWeakObjectPtr<UWidget_Quest> Widget, UQuest* Data)
{
	QuestWidget = Widget;
	Quest = Data;
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

void UWidget_QuestInfo::RegisterQuickQuest()
{
	UE_LOG(LogTemp, Warning, TEXT("REGISTER QUEST"));
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	GInstance->GetQuestMgr()->BindQuickWindow(MyPlayer, Quest);
}
