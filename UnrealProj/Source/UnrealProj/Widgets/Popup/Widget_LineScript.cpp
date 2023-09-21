// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_LineScript.h"
#include "../../Creatures/Npc/Npc.h"
#include "Components/TextBlock.h"

void UWidget_LineScript::NativeConstruct()
{

}

void UWidget_LineScript::BindScript(UDataTable* ScriptData, FString NpcName)
{
	// 스크립트 연동 후, 첫 스크립트 열기
	Script = ScriptData;
	Text_Name->SetText(FText::FromString(NpcName));
	UpdateLine(NextPage);
}

void UWidget_LineScript::OpenFollowingLine()
{
	int Cnt = Script->GetRowNames().Num();

	if (NextPage > Cnt)
	{
		// 퀘스트 수락할 지 말 지
	}
	else
	{
		UpdateLine(NextPage);
	}
}

void UWidget_LineScript::UpdateLine(int Page)
{
	FString Line = Script->FindRow<FScriptData>(*FString::FromInt(Page), TEXT(""))->Line;
	NextPage++;
}
