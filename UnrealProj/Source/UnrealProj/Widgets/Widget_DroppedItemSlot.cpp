// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_DroppedItemSlot.h"
#include "../MyGameInstance.h"
#include "Components/RichTextBlock.h"
#include "Components/Image.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../Inventory/Inventory.h"
#include "Popup/Widget_ItemDrop.h"
#include "Kismet/GameplayStatics.h"

void UWidget_DroppedItemSlot::SetInfo(FMiscItemData* NewItem, UWidget_ItemDrop* BWidget)
{
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	ItemId = NewItem->Id;
	Img_Item->SetBrush(GInstance->GetMiscItemImage(NewItem->Id)->Brush);
	Text_ItemName->SetText(FText::FromString(NewItem->Name));
	BaseWidget = BWidget;
	
}

FReply UWidget_DroppedItemSlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) == true)
		return Reply.NativeReply;

	UE_LOG(LogTemp, Warning, TEXT("Double Clicked!"));
	GetItem();
	RemoveThis();
	
	return Reply.NativeReply;
}

void UWidget_DroppedItemSlot::GetItem()
{
	UE_LOG(LogTemp, Warning, TEXT("Get Item -- -- "));
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);

	auto Inven = MyPlayer->GetInventory();
	Inven->GainNewItem(ITEM_MISC, ItemId); //ITEM_MISC를 나중에 IType으로 변경
}

void UWidget_DroppedItemSlot::RemoveThis()
{
	BaseWidget->RemoveSlot(this);
}
