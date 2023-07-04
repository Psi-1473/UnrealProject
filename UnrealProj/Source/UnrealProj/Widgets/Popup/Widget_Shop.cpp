// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Shop.h"
#include "../../MyGameInstance.h"
#include "../../Creatures/Npc/Npc.h"
#include "Components/Button.h"

void UWidget_Shop::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Exit->OnClicked.AddDynamic(this, &UWidget_Shop::CloseUI);
}

void UWidget_Shop::CreateSlot(TWeakObjectPtr<class ANpc> Npc)
{
}

void UWidget_Shop::CloseUI()
{
	auto GInstance = Cast<UMyGameInstance>(OwnerNpc->GetGameInstance());
	GInstance->GetUIMgr()->CloseUI(UIType::Shop);
}
