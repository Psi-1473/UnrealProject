// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_InvenSlot.h"
#include "Components/RichTextBlockImageDecorator.h"
#include "../../Items/Item.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UWidget_InvenSlot::NativeConstruct()
{
}

void UWidget_InvenSlot::SetImage()
{
	if (SlotItem == nullptr) return;

	Img_Item->SetBrush(SlotItem->GetItemImage()->Brush);
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
		Text_Count->SetText(FText::FromString(Cnt));
	}
}
