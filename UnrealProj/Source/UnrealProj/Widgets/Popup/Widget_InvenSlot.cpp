// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_InvenSlot.h"
#include "Components/RichTextBlockImageDecorator.h"
#include "../../Items/Item.h"
#include "../../Items/Weapons/Weapon.h"
#include "../../Items/UseItem/UseItem.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "../../MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "../DragWidget.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Inventory/Inventory.h"
#include "Widget_Inventory.h"


UWidget_InvenSlot::UWidget_InvenSlot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UWidget_InvenSlot::NativeConstruct()
{
}

FReply UWidget_InvenSlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
	
	if(InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) == true)
		return Reply.NativeReply;

	UE_LOG(LogTemp, Warning, TEXT("Double Clicked!"));
	if (SlotItem != nullptr)
	{
		SlotItem->UseItem(SlotIndex);
		InvenWidget->UpdateSlotInfo();
	}

	return Reply.NativeReply;
}

FReply UWidget_InvenSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if(InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) == true)
		return Reply.NativeReply;


	Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

	return Reply.NativeReply;
}


void UWidget_InvenSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (OutOperation == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Draging Start"));

		UDragWidget* DragOper = NewObject<UDragWidget>();
		OutOperation = DragOper;
		DragOper->SlotItem = SlotItem;
		DragOper->Type = DragType::Item;
		DragOper->SlotIndex = SlotIndex;
		DragOper->bFromQuickSlot = false;

		if (DragVisualClass != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Widget Created"));
			UWidget_InvenSlot* VisualWidget = CreateWidget<UWidget_InvenSlot>(GetWorld(), DragVisualClass);
			VisualWidget->SetVisibility(ESlateVisibility::Visible);

			VisualWidget->SlotIndex = this->SlotIndex;
			VisualWidget->SetItem(SlotItem);
			VisualWidget->SetImage();
			VisualWidget->SetPositionInViewport(InMouseEvent.GetScreenSpacePosition());
			DragOper->DefaultDragVisual = VisualWidget;
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Draging Again"));
	}
}

bool UWidget_InvenSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{

	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	UDragWidget* DragOper = Cast<UDragWidget>(InOperation);

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Draging End"));

	if (DragOper != nullptr)
	{
		if (DragOper->SlotIndex == this->SlotIndex)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Same Return"));
			return true;
		}

		if (DragOper->bFromQuickSlot)
			return false;
		// 스왑
		// 1. Inventory 정보 변경
		// 2. 업데이트
		auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		auto MyPlayer = Cast<AMyPlayer>(Char);
		MyPlayer->GetInventory()->SwapItem(DragOper->SlotIndex, SlotIndex);
		InvenWidget->UpdateSlotInfo();
		return true;
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Draging false"));
		return false;
	}
}


void UWidget_InvenSlot::SetImage()
{
	if (SlotItem == nullptr)
	{
		Img_Item->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("SET IMAGE FUNC"));
	Img_Item->SetVisibility(ESlateVisibility::Visible);
	auto GInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Img_Item->SetBrush(SlotItem->GetItemImage(GInstance)->Brush);
}
void UWidget_InvenSlot::SetImage(UImage* Img)
{
	Img_Item->SetBrush(Img->Brush);
}


void UWidget_InvenSlot::SetCount()
{
	if (SlotItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NULL SLOT"));
		Text_Count->SetText(FText::FromString(TEXT("")));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NOT NULL SLOT"));
		FString Cnt = FString::FromInt(SlotItem->GetCount());
		if (Cnt == TEXT("0"))
			Text_Count->SetText(FText::FromString(TEXT("")));
		else
			Text_Count->SetText(FText::FromString(Cnt));
	}
}
