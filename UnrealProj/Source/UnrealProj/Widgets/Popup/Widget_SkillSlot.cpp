// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_SkillSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../../Skills/Skill.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "../DragWidget.h"
#include "Widget_InvenSlot.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Widget_Information.h"

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
			VisualWidget->SetImage(Skill->GetTexture());
			VisualWidget->SetPositionInViewport(InMouseEvent.GetScreenSpacePosition());
			DragOper->DefaultDragVisual = VisualWidget;
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Draging Again"));
	}
}

void UWidget_SkillSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);


	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Mouse Enter"));

	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);
	UUserWidget* Widget = MyPlayer->GetInstance()->GetUIMgr()->PopupUI(GetWorld(), UIType::Information);
	if (Widget == nullptr) return;

	UWidget_Information* InfoWidget = Cast<UWidget_Information>(Widget);
	if (InfoWidget == nullptr) return;


	FGeometry Geometry = GetCachedGeometry();
	FVector2D Position = Geometry.GetAbsolutePosition();
	Position.X += 200.f;
	Position.Y -= 100.f;
	InfoWidget->SetPosition(Position);
	InfoWidget->SetInfoBySkill(Skill);

}

void UWidget_SkillSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Mouse Leave"));

	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);
	MyPlayer->GetInstance()->GetUIMgr()->CloseUI(UIType::Information);

}

void UWidget_SkillSlot::SetInfo()
{
	Img_Skill->SetBrushFromTexture(Skill->GetTexture());
	Text_Name->SetText(FText::FromString(*(Skill->GetSkillName())));
}
