// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_InvenSlot.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_InvenSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void SetItem(class AItem* ItemValue) { SlotItem = ItemValue; }
	void SetImage();
	void SetCount();
	void SetSlotIndex(int16 Value) { SlotIndex = Value; }


	class AItem* GetItem() { return SlotItem; }
private:
	UPROPERTY()
	class AItem* SlotItem;

	UPROPERTY()
	int16 SlotIndex;
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Count;
	
	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Item;
};
