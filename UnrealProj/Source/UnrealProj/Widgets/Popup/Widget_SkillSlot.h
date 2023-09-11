// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_SkillSlot.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_SkillSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

	void SetSkill(class UPlayerSkill* Value) { Skill = Value; }
	void SetInfo();

private:
	UPROPERTY()
	class UPlayerSkill* Skill;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Skill;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UWidget_InvenSlot> DragVisualClass;
};
