// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_DroppedItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_DroppedItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetInfo(struct FMiscItemData* NewItem);

	// + 더블클릭함수 추가

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Item;

	UPROPERTY(meta = (BindWidget))
	class URichTextBlock* Text_ItemName;

private:
	UPROPERTY()
	int ItemId;

	UPROPERTY()
	class UWidget_ItemDrop* BaseWidget;

};
