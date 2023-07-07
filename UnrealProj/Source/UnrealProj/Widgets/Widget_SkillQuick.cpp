// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_SkillQuick.h"
#include "DragWidget.h"
#include "Components/Image.h"
#include "../Skills/Skill.h"

bool UWidget_SkillQuick::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	UDragWidget* DragOper = Cast<UDragWidget>(InOperation);

	if (DragOper != nullptr)
	{
		if (DragOper->Type != DragType::Skill)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag Quick : Not Skill"));
			return true;
		}

		if (DragOper->SlotIndex == QuickSlotIndex)
			return true;

		if (DragOper->bFromQuickSlot == false)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag Quick : Skill Droped"));
			QuickSkill = DragOper->Skill;
			SetImage(QuickSkill->GetTexture());
			// Ű�� ��ų ���
			return true;
		}
		else
		{
			// �����Գ��� ����
			//MainWidget->SwapItemQuickSlot(DragOper->SlotIndex, QuickSlotIndex);
			return true;
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Draging false"));
		return false;
	}
}

void UWidget_SkillQuick::SetImage(UTexture2D* Texture)
{
	Img_Object->SetBrushFromTexture(Texture);
}
