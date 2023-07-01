// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Script.h"
#include "../../Creatures/Npc/Npc.h"
#include "Components/TextBlock.h"

void UWidget_Script::SetScript(ANpc* Npc)
{
	Text_Name->SetText(FText::FromString(*Npc->GetName()));
	Text_Script->SetText(FText::FromString(*Npc->GetDefaultLine()));
}
