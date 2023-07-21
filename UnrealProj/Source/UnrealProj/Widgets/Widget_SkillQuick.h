// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget_QuickSlot.h"
#include "Widget_SkillQuick.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_SkillQuick : public UWidget_QuickSlot
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	void SetSkill(class UPlayerSkill* Skill);
	virtual void SetImage() override;

	class UPlayerSkill* GetSkill() { return QuickSkill; }
private:
	UPROPERTY()
	class UPlayerSkill* QuickSkill;
};
