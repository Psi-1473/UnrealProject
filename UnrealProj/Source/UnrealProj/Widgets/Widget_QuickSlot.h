// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_QuickSlot.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_QuickSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetSlotIndex(int Value) { QuickSlotIndex = Value; }
	void SetMainWidget(TWeakObjectPtr<class UWidget_PlayerMain> Widget) { MainWidget = Widget; }

	class UTextBlock* GetTextKey() { return Text_Key; }
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

protected:
	UPROPERTY()
	int QuickSlotIndex;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Object;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Key;

	UPROPERTY()
	TWeakObjectPtr<class UWidget_PlayerMain> MainWidget;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UWidget_InvenSlot> DragVisualClass;
	
};
