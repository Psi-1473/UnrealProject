// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_LineScript.h"
#include "../../Creatures/Npc/Npc.h"
#include "../../Managers/UIManager.h"
#include "../../MyGameInstance.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../../DEFINE.h"
#include "Engine/DataTable.h"


void UWidget_LineScript::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Next->OnClicked.AddDynamic(this, &UWidget_LineScript::OpenFollowingLine);
}

void UWidget_LineScript::BindScript(UDataTable* ScriptData, FString NpcName)
{
	// 스크립트 연동 후, 첫 스크립트 열기
	if(ScriptData != nullptr)
		Script = ScriptData;
	Text_Name->SetText(FText::FromString(NpcName));
	NextPage = 1;
	UpdateLine(NextPage);
}

void UWidget_LineScript::OpenFollowingLine()
{
	int Cnt = Script->GetRowNames().Num();

	if (NextPage > Cnt)
	{
		// 퀘스트 수락할 지 말 지
		auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
		if (GInstance == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("GInstance Null"));
			return;
		}

		GInstance->GetUIMgr()->CloseUI((int)UIType::LineScript);
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
