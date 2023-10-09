// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../DEFINE.h"
#include "Widget_SkillSlot.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_SkillSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

	UFUNCTION()
	void SkillLevelUp();

	void SetSkill();
	void SetInfo();

private:
	UPROPERTY()
	bool bInformation = false;

	UPROPERTY(EditAnywhere)
	SkillEnum eSkill;

	UPROPERTY()
	class UPlayerSkill* Skill;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Skill;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Level;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_LevelUp;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UWidget_InvenSlot> DragVisualClass;
};
