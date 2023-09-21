// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_NpcQuestSlot.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "Widget_NpcQuest.h"
#include "../../Managers/UIManager.h"



void UWidget_NpcQuestSlot::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_QuestName->OnClicked.AddDynamic(this, &UWidget_NpcQuestSlot::UpdateQuestInfo);
}

void UWidget_NpcQuestSlot::Init(UWidget_NpcQuest* QWidget, FQuestData* QData)
{
	QuestWidget = QWidget;
	QuestData = *QData;

	Text_QuestName->SetText(FText::FromString(QuestData.Name));
}

void UWidget_NpcQuestSlot::PopupQuestLineScript()
{
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);

	auto GInstance = Cast<UMyGameInstance>(MyPlayer->GetGameInstance());
	GInstance->GetUIMgr()->CloseAllUI();
	GInstance->GetUIMgr()->PopupUI(GetWorld(), UIType::LineScript);
	//  LineScript ���ε�
}

void UWidget_NpcQuestSlot::UpdateQuestInfo()
{
	// �̰� �ߵ��� �ȵ˴ϴ�.....
	UE_LOG(LogTemp, Warning, TEXT("Update QuestInfo"));
	QuestWidget->UpdateInfo(QuestData);
}
