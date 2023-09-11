// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_ItemQuick.h"
#include "DragWidget.h"
#include "../DEFINE.h"
#include "Components/Image.h"
#include "../Items/Item.h"
#include "../MyGameInstance.h"
#include "Popup/Widget_InvenSlot.h"
#include "Widget_PlayerMain.h"
#include "Components/TextBlock.h"
#include "../Items/Weapons/Weapon.h"


void UWidget_ItemQuick::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	if (QuickItem == nullptr) return;

	if (OutOperation == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Draging Start"));

		UDragWidget* DragOper = NewObject<UDragWidget>();
		OutOperation = DragOper;
		DragOper->SlotItem = QuickItem;
		DragOper->Type = DragType::Item;
		DragOper->SlotIndex = QuickSlotIndex;
		DragOper->bFromQuickSlot = true;

		if (DragVisualClass != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Widget Created"));
			UWidget_InvenSlot* VisualWidget = CreateWidget<UWidget_InvenSlot>(GetWorld(), DragVisualClass);
			VisualWidget->SetVisibility(ESlateVisibility::Visible);

			//VisualWidget->SlotIndex = QuickSlotIndex;
			VisualWidget->SetItem(QuickItem);
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

bool UWidget_ItemQuick::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	UDragWidget* DragOper = Cast<UDragWidget>(InOperation);

	if (DragOper != nullptr)
	{
		if (DragOper->Type != DragType::Item)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag Quick : Not Item"));
			return true;
		}

		if (DragOper->SlotIndex == QuickSlotIndex && DragOper->bFromQuickSlot)
			return true;

		if (Cast<AWeapon>(DragOper->SlotItem) != nullptr)
			return true;

		if (DragOper->bFromQuickSlot == false)
		{
			SetItem(DragOper->SlotItem);
			MainWidget->CheckRegisteredItem(DragOper->SlotItem, QuickSlotIndex);
			return true;
		}
		else
		{
			// Äü½½·Ô³¢¸® ½º¿Ò
			if (QuickItem != nullptr) QuickItem->SetQuickSlotIndex(-1);
			MainWidget->SwapItemQuickSlot(DragOper->SlotIndex, QuickSlotIndex);
			return true;
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Draging false"));
		return false;
	}
}

void UWidget_ItemQuick::SetItem(AItem* Item)
{
	QuickItem = Item;
	SetImage();
	SetTextCount();

	if (QuickItem == nullptr) return;
	Item->SetQuickSlotIndex(QuickSlotIndex);
}

void UWidget_ItemQuick::SetImage()
{
	if (QuickItem == nullptr)
	{
		Img_Object->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	Img_Object->SetVisibility(ESlateVisibility::Visible);
	Img_Object->SetBrush(QuickItem->GetItemImage(Cast<UMyGameInstance>(GetWorld()->GetGameInstance()))->Brush);
}

void UWidget_ItemQuick::UseItem()
{
	if (QuickItem == nullptr)
		return;

	QuickItem->UseItem();
	SetTextCount();
}

void UWidget_ItemQuick::SetTextCount()
{
	if (QuickItem == nullptr)
	{
		Text_Count->SetText(FText::FromString(TEXT("")));
		return;
	}
	Text_Count->SetText(FText::FromString(FString::FromInt(QuickItem->GetCount())));
}
