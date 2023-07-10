// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget_QuickSlot.h"
#include "Widget_ItemQuick.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_ItemQuick : public UWidget_QuickSlot
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	class AItem* GetItem() { return QuickItem; }

	void SetItem(class AItem* Item);
	virtual void SetImage() override;
	void UseItem();
	void SetTextCount();
private:
	
	//void SetCount();
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Count;

	UPROPERTY()
	class AItem* QuickItem;


};
