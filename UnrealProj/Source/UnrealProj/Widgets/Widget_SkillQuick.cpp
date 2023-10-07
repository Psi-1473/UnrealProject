// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_SkillQuick.h"
#include "DragWidget.h"
#include "Components/Image.h"
#include "../Skills/Skill.h"
#include "../Skills/Player/PlayerSkill.h"
#include "../Skills/Components/PlayerSkillComponent.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../MyGameInstance.h"
#include "Components/ProgressBar.h"
#include "Popup/Widget_InvenSlot.h"
#include "Widget_PlayerMain.h"

void UWidget_SkillQuick::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidget_SkillQuick::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	if (QuickSkill == nullptr) return;

	if (OutOperation == nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Draging Start"));

		UDragWidget* DragOper = NewObject<UDragWidget>();
		OutOperation = DragOper;
		DragOper->Skill = QuickSkill;
		DragOper->Type = DragType::Skill;
		DragOper->SlotIndex = QuickSlotIndex;
		DragOper->bFromQuickSlot = true;

		if (DragVisualClass != nullptr)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Widget Created"));
			UWidget_InvenSlot* VisualWidget = CreateWidget<UWidget_InvenSlot>(GetWorld(), DragVisualClass);
			VisualWidget->SetVisibility(ESlateVisibility::Visible);
			VisualWidget->SetImage(QuickSkill->GetTexture());
			VisualWidget->SetPositionInViewport(InMouseEvent.GetScreenSpacePosition());
			DragOper->DefaultDragVisual = VisualWidget;
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Draging Again"));
	}
}

bool UWidget_SkillQuick::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	UDragWidget* DragOper = Cast<UDragWidget>(InOperation);

	if (DragOper != nullptr)
	{
		if (DragOper->Skill == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag Quick : Skill NULL"));
			return false;
		}
		if (DragOper->Type != DragType::Skill)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag Quick : Not Skill"));
			return true;
		}

		if (DragOper->SlotIndex == QuickSlotIndex)
			return true;

		if (DragOper->bFromQuickSlot == false)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag Quick : Skill Droped"));
			SetSkill(DragOper->Skill);
			// 키에 스킬 등록

			auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
			GInstance->CheckQuest(QUEST_ETC, ETC_QUICKSLOT, DragOper->Skill->GetOwnerPlayer());
			QuickSkill->GetOwnerPlayer()->GetSkillComponent()->RegisterSkill(QuickSlotIndex, QuickSkill);
			return true;
		}
		else
		{
			// 퀵슬롯끼리 스왑
			if(MainWidget == nullptr)
				return false;
			MainWidget->SwapSkillQuickSlot(DragOper->Skill->GetOwnerPlayer()->GetSkillComponent(), DragOper->SlotIndex, QuickSlotIndex);
			return true;
		}


	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Draging false"));
		return false;
	}
}

void UWidget_SkillQuick::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (QuickSkill == nullptr)
		return;

	float Ratio = QuickSkill->GetCooldownRatio();
	PB_Cooldown->SetPercent(Ratio);

}

void UWidget_SkillQuick::SetSkill(UPlayerSkill* Skill)
{
	QuickSkill = Skill;

	// 여기서 실행
	SetImage();
}

void UWidget_SkillQuick::SetImage()
{
	Super::SetImage();
	if (QuickSkill == nullptr)
	{
		Img_Object->SetVisibility(ESlateVisibility::Hidden);
		PB_Cooldown->SetPercent(0.f);
		return;
	}
	Img_Object->SetVisibility(ESlateVisibility::Visible);
	Img_Object->SetBrushFromTexture(QuickSkill->GetTexture());
}


