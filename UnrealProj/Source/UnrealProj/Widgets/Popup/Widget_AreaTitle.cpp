// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_AreaTitle.h"
#include "Components/TextBlock.h"
#include "../../Triggers/AreaBox.h"
#include "../../MyGameInstance.h"
#include "../../Managers/UIManager.h"
#include "../../DEFINE.h"

void UWidget_AreaTitle::Init(AAreaBox* Area)
{
	Text_Name->SetText(FText::FromString(Area->GetAreaName()));
	Area->GetWorldTimerManager().SetTimer(DestroyTimer, this, &UWidget_AreaTitle::CloseThis, 3.f, false);
}

void UWidget_AreaTitle::CloseThis()
{
	auto GInstance = Cast<UMyGameInstance>(GetGameInstance());
	GInstance->GetUIMgr()->CloseUI((int)UIType::AreaTitle);
}
