// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Script.h"
#include "../../Creatures/Npc/Npc.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../../MyGameInstance.h"
#include "Widget_Shop.h"


void UWidget_Script::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Shop->OnClicked.AddDynamic(this, &UWidget_Script::PopupShopWidget);
	Btn_Exit->OnClicked.AddDynamic(this, &UWidget_Script::CloseUI);
}

void UWidget_Script::SetScript(TWeakObjectPtr<class ANpc> Npc)
{
	Text_Name->SetText(FText::FromString(*Npc->GetName()));
	Text_Script->SetText(FText::FromString(*Npc->GetDefaultLine()));
	OwnerNpc = Npc;

	if (OwnerNpc->GetNpcType() == NONE_SHOP)
		Btn_Shop->SetVisibility(ESlateVisibility::Hidden);
}

void UWidget_Script::PopupShopWidget()
{
	if (OwnerNpc == nullptr)
		return;

	auto GInstance = Cast<UMyGameInstance>(OwnerNpc->GetGameInstance());
	auto ShopUI = GInstance->GetUIMgr()->PopupUI(OwnerNpc->GetWorld(), UIType::Shop);
	auto Shop = Cast<UWidget_Shop>(ShopUI);
	Shop->SetOwnerNpc(OwnerNpc);
	Shop->CreateSlot(OwnerNpc);
}

void UWidget_Script::CloseUI()
{
	auto GInstance = Cast<UMyGameInstance>(OwnerNpc->GetGameInstance());
	GInstance->GetUIMgr()->CloseUI(UIType::Script);
}
