// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_LineScript.h"
#include "../../Creatures/Npc/Npc.h"
#include "Components/TextBlock.h"

void UWidget_LineScript::NativeConstruct()
{

}

void UWidget_LineScript::BindScript(UDataTable* ScriptData, FString NpcName)
{
	// ��ũ��Ʈ ���� ��, ù ��ũ��Ʈ ����
	Script = ScriptData;
	Text_Name->SetText(FText::FromString(NpcName));
	UpdateLine(NextPage);
}

void UWidget_LineScript::OpenFollowingLine()
{
	int Cnt = Script->GetRowNames().Num();

	if (NextPage > Cnt)
	{
		// ����Ʈ ������ �� �� ��
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
