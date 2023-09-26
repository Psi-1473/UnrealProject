// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_NpcQuestClear.h"
#include "../../MyGameInstance.h"
#include "../../Creatures/Npc/Npc.h"
#include "../../ActorComponent/QuestComponent.h"
#include "../../ActorComponent/PlayerQuestComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../ActorComponent/PlayerQuestComponent.h"
#include "../../DataClass/Quest.h"
#include "Widget_Script.h"

void UWidget_NpcQuestClear::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Complete->OnClicked.AddDynamic(this, &UWidget_NpcQuestClear::CompleteQuest);
}

void UWidget_NpcQuestClear::CompleteQuest()
{
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);

	MyPlayer->GetQuestComponent()->ClearQuest(Quest);

	ResetUI();
}

void UWidget_NpcQuestClear::BindQuest(UMyGameInstance* GInstance, TWeakObjectPtr<class ANpc> Npc, UQuest* QuestData)
{
	OwnerNpc = Npc;
	Quest = QuestData;

	Text_QuestTitle->SetText(FText::FromString(QuestData->GetQuestName()));
	Text_QuestInfo->SetText(FText::FromString(QuestData->GetQuestExplanation()));
}

void UWidget_NpcQuestClear::ResetUI()
{
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());

	GInstance->GetUIMgr()->CloseAllUI();
	auto Widget = GInstance->GetUIMgr()->PopupUI(GetWorld(), UIType::Script);
	auto WScript = Cast<UWidget_Script>(Widget);
	WScript->SetScript(OwnerNpc);
}
