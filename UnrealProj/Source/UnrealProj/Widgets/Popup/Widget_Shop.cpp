// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Shop.h"
#include "../../MyGameInstance.h"
#include "../../Creatures/Npc/Npc.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Widget_ShopSlot.h"

UWidget_Shop::UWidget_Shop(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> SA(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Slots/WBP_ShopSlot.WBP_ShopSlot_C'"));
	if (SA.Succeeded()) BP_Slot = SA.Class;
}

void UWidget_Shop::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Exit->OnClicked.AddDynamic(this, &UWidget_Shop::CloseUI);
}

void UWidget_Shop::CreateSlot(TWeakObjectPtr<class ANpc> Npc)
{
	int ItemNumber = Npc->GetSwordIds().Num();
	auto GInstance = Cast<UMyGameInstance>(Npc->GetGameInstance());
	for (int i = 0; i < ItemNumber; i++)
	{
		Slot = CreateWidget(GetWorld(), BP_Slot);
		SlotBox->AddChild(Slot);
		auto ShopSlot = Cast<UWidget_ShopSlot>(Slot);
		ShopSlot->SetSlot(GInstance, ITEM_SWORD, Npc->GetSwordIds()[i]);
	}
	ItemNumber = Npc->GetBowIds().Num();
	for (int i = 0; i < ItemNumber; i++)
	{
		Slot = CreateWidget(GetWorld(), BP_Slot);
		SlotBox->AddChild(Slot);
		auto ShopSlot = Cast<UWidget_ShopSlot>(Slot);
		ShopSlot->SetSlot(GInstance, ITEM_BOW, Npc->GetBowIds()[i]);
	}
	ItemNumber = Npc->GetUseItemIds().Num();
	for (int i = 0; i < ItemNumber; i++)
	{
		Slot = CreateWidget(GetWorld(), BP_Slot);
		SlotBox->AddChild(Slot);
		auto ShopSlot = Cast<UWidget_ShopSlot>(Slot);
		ShopSlot->SetSlot(GInstance, ITEM_USE, Npc->GetUseItemIds()[i]);
	}
	
}

void UWidget_Shop::CloseUI()
{
	auto GInstance = Cast<UMyGameInstance>(OwnerNpc->GetGameInstance());
	GInstance->GetUIMgr()->CloseUI(UIType::Shop);
}
