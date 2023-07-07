// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_QuickSlot.h"
#include "Components/TextBlock.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

FReply UWidget_QuickSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) == true)
		return Reply.NativeReply;


	Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

	return Reply.NativeReply;
}

