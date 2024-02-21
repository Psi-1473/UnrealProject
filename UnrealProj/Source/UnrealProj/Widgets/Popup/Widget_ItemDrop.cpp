// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_ItemDrop.h"
#include "Components/ScrollBox.h"
#include "../Widget_DroppedItemSlot.h"
#include "../../MyGameInstance.h"
#include "../../Managers/UIManager.h"
#include "../../Managers/ResourceManager.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../State/StateMachine.h"
#include "Kismet/GameplayStatics.h"
#include "../../Creatures/Npc/DropItem.h"
#include "GameFramework/Actor.h"

UWidget_ItemDrop::UWidget_ItemDrop(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> SLOT(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Slots/WBP_DroppedItemSlot.WBP_DroppedItemSlot_C'"));
	if (SLOT.Succeeded()) BP_Slot = SLOT.Class;
}

void UWidget_ItemDrop::CreateSlot(TArray<FMiscItemData*> MiscItems)
{
	for (int i = 0; i < MiscItems.Num(); i++)
	{
		UUserWidget* NewSlot = CreateWidget(GetWorld(), BP_Slot);
		ScrollBox_ItemList->AddChild(NewSlot);
		UWidget_DroppedItemSlot* DSlot = Cast<UWidget_DroppedItemSlot>(NewSlot);
		DSlot->SetInfo(MiscItems[i], this);
		Slots.Add(DSlot);
	}
}

void UWidget_ItemDrop::GetAllItems()
{
	UE_LOG(LogTemp, Warning, TEXT("Get All Items"));
	TArray< UWidget_DroppedItemSlot*> DeleteSlots;
	for (UWidget_DroppedItemSlot* slot : Slots)
	{
		slot->GetItem();
		DeleteSlots.Add(slot);
	}

	for(UWidget_DroppedItemSlot * slot : DeleteSlots)
		RemoveSlot(slot);
}

void UWidget_ItemDrop::RemoveSlot(UWidget_DroppedItemSlot* RSlot)
{
	Slots.Remove(RSlot);
	RSlot->RemoveFromParent();

	if (Slots.Num() <= 0)
	{
		CloseUI();
		DestroyDropItem();
	}
}

void UWidget_ItemDrop::CloseUI()
{
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	GInstance->GetUIMgr()->CloseUI((int)UIType::ItemDrop);

	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);
	MyPlayer->GetStateMachine()->SetState(STATE::IDLE);
}

void UWidget_ItemDrop::DestroyDropItem()
{
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	GInstance->GetResourceMgr()->Destroy<ADropItem>(DropItem);
}

void UWidget_ItemDrop::SetDropItem(ADropItem* DItem)
{
	DropItem = DItem;
}
