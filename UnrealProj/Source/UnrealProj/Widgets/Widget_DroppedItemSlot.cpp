// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_DroppedItemSlot.h"
#include "../MyGameInstance.h"
#include "Components/RichTextBlock.h"
#include "Components/Image.h"

void UWidget_DroppedItemSlot::SetInfo(FMiscItemData* NewItem)
{
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	Img_Item->SetBrush(GInstance->GetMiscItemImage(NewItem->Id)->Brush);
	Text_ItemName->SetText(FText::FromString(NewItem->Name));
	
}
