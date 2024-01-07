// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Revive.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Managers/UIManager.h"
#include "../../MyGameInstance.h"
#include "Components/Button.h"

void UWidget_Revive::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Revive->OnClicked.AddDynamic(this, &UWidget_Revive::ClickRevive);
}

void UWidget_Revive::SetPlayer(AMyPlayer* PlayerValue)
{
	Player = PlayerValue;
}

void UWidget_Revive::ClickRevive()
{
	if(Player == nullptr)
		return;

	auto GInstance = Cast<UMyGameInstance>(Player->GetGameInstance());
	GInstance->GetUIMgr()->CloseUI((int)UIType::Revive);
	Player->Revive();
}
