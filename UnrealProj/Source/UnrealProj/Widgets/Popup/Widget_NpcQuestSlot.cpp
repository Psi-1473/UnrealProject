// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_NpcQuestSlot.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Creatures/Npc/Npc.h"
#include "Widget_NpcQuest.h"
#include "../../Managers/UIManager.h"
#include "Widget_NpcQuestInfo.h"
#include "Widget_LineScript.h"



void UWidget_NpcQuestSlot::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_QuestName->OnClicked.AddDynamic(this, &UWidget_NpcQuestSlot::PopupQuestLineScript);
}

void UWidget_NpcQuestSlot::Init(TWeakObjectPtr<class ANpc> Npc, FQuestData* NewQuestData)
{
	OwnerNpc = Npc;
	QuestData = *NewQuestData;
	Text_QuestName->SetText(FText::FromString(QuestData.Name));
}

void UWidget_NpcQuestSlot::PopupQuestLineScript()
{
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);

	auto GInstance = Cast<UMyGameInstance>(MyPlayer->GetGameInstance());
	GInstance->GetUIMgr()->CloseAllUI();
	auto Widget = GInstance->GetUIMgr()->PopupUI(GetWorld(), UIType::LineScript);
	auto LineScript = Cast<UWidget_LineScript>(Widget);
	LineScript->BindQuestScript(GInstance, OwnerNpc, QuestData.Id);
	//  LineScript ���ε�
}

