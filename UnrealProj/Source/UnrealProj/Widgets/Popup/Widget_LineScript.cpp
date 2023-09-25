// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_LineScript.h"
#include "../../Creatures/Npc/Npc.h"
#include "../../Managers/UIManager.h"
#include "../../MyGameInstance.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Widget_NpcQuestInfo.h"
#include "../../DEFINE.h"
#include "Engine/DataTable.h"


void UWidget_LineScript::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Next->OnClicked.AddDynamic(this, &UWidget_LineScript::OpenFollowingLine);
}

void UWidget_LineScript::BindQuestScript(UMyGameInstance* GInstance, TWeakObjectPtr<ANpc> Npc, int32 BindQuestId)
{
	OwnerNpc = Npc;
	QuestId = BindQuestId;
	NextPage = 1;

	Script = GInstance->GetQuestScript(OwnerNpc->GetId(), QuestId);
	Text_Name->SetText(FText::FromString(OwnerNpc->GetNpcName()));

	UpdateLine(NextPage);
}

void UWidget_LineScript::OpenFollowingLine()
{
	int Cnt = Script->GetRowNames().Num();

	if (NextPage > Cnt)
	{
		// 퀘스트 수락할 지 말 지, 나중에는 스크립트 타입 변수를 두어 타입에 따라 실행함수 바꾸기
		auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
		auto Widget = GInstance->GetUIMgr()->PopupUI(GetWorld(), UIType::NpcQuestInfo);
		auto QInfo = Cast<UWidget_NpcQuestInfo>(Widget);
		QInfo->BindQuest(GInstance, OwnerNpc, QuestId);
	}
	else
	{
		UpdateLine(NextPage);
	}
}

void UWidget_LineScript::UpdateLine(int Page)
{
	if(Script == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Update Line : Script NULL"), Page);
	UE_LOG(LogTemp, Warning, TEXT("Update Line : %d"), Page);
	FString Line = Script->FindRow<FScriptData>(*FString::FromInt(Page), TEXT(""))->Line;
	Text_Script->SetText(FText::FromString(Line));
	NextPage++;
}
