// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_SkillSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../../Skills/Skill.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "../DragWidget.h"
#include "Widget_InvenSlot.h"

FReply UWidget_SkillSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) == true)
		return Reply.NativeReply;


	Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

	return Reply.NativeReply;
}

void UWidget_SkillSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (OutOperation == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Draging Start"));

		UDragWidget* DragOper = NewObject<UDragWidget>();
		OutOperation = DragOper;
		DragOper->Skill = Skill;
		DragOper->Type = DragType::Skill;
		DragOper->bFromQuickSlot = false;
		DragOper->SlotIndex = -1;

		if (DragVisualClass != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Widget Created"));
			UWidget_InvenSlot* VisualWidget = CreateWidget<UWidget_InvenSlot>(GetWorld(), DragVisualClass);
			VisualWidget->SetVisibility(ESlateVisibility::Visible);
			VisualWidget->SetImage(Img_Skill);
			VisualWidget->SetPositionInViewport(InMouseEvent.GetScreenSpacePosition());
			DragOper->DefaultDragVisual = VisualWidget;
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Draging Again"));
	}
}

void UWidget_SkillSlot::SetInfo()
{
	Img_Skill->SetBrushFromTexture(Skill->GetTexture());
	Text_Name->SetText(FText::FromString(*(Skill->GetSkillName())));
}
