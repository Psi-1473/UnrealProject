// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_NpcQuestInfo.h"
#include "../../MyGameInstance.h"
#include "../../Creatures/Npc/Npc.h"
#include "../../ActorComponent/QuestComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../ActorComponent/PlayerQuestComponent.h"
#include "Widget_Script.h"
#include "Widget_NpcQuest.h"

void UWidget_NpcQuestInfo::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Okay->OnClicked.AddDynamic(this, &UWidget_NpcQuestInfo::TakeQuest);
	Btn_Refuse->OnClicked.AddDynamic(this, &UWidget_NpcQuestInfo::RefuseQuest);
}

void UWidget_NpcQuestInfo::TakeQuest()
{
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);
	MyPlayer->GetQuestComponent()->TakeNewQuest(Cast<ANpc>(OwnerNpc), QuestId);

	ResetUI();

}

void UWidget_NpcQuestInfo::RefuseQuest()
{
	ResetUI();
}

void UWidget_NpcQuestInfo::BindQuest(UMyGameInstance* GInstance, TWeakObjectPtr<class ANpc> Npc, int32 BindQuestId)
{
	OwnerNpc = Npc;
	QuestId = BindQuestId;
	FQuestData QData = *(OwnerNpc->GetQuestComponent()->GetPossibleQuestDataByQuestIndex(QuestId));

	Text_QuestTitle->SetText(FText::FromString(QData.Name));
	Text_QuestInfo->SetText(FText::FromString(QData.Explanation));
}

void UWidget_NpcQuestInfo::ResetUI()
{
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());

	GInstance->GetUIMgr()->CloseAllUI();
	auto Widget = GInstance->GetUIMgr()->PopupUI(GetWorld(), UIType::Script);
	auto WScript = Cast<UWidget_Script>(Widget);
	WScript->SetScript(OwnerNpc);
}
