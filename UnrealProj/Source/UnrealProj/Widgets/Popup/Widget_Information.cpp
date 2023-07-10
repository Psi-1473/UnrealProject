// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Information.h"
#include "../../MyGameInstance.h"

void UWidget_Information::SetInfo(InformationType Type, int Id)
{
	FString Name;
	FString Sub;

	// GInstance 가져오기
	if (Type == INFO_ITEM)
	{
		// Name = GInstance를 통해 불러온 아이템 데이터의 Name
		// Sub = GInstance를 통해 불러온 아이템 데이터의 Sub
	}
	else if (Type == INFO_SKILL)
	{
		// 검스킬인지 활스킬인지 확인필요할듯
	}
}
