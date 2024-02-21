// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_ItemDrop.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_ItemDrop : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UWidget_ItemDrop(const FObjectInitializer& ObjectInitializer);
	void CreateSlot(TArray<struct FMiscItemData*> MiscItems);
	void GetAllItems();
	
	void RemoveSlot(class UWidget_DroppedItemSlot* RSlot);
	void CloseUI();
	void DestroyDropItem();
	void SetDropItem(class ADropItem* DItem);


private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_ReceiveAll;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ScrollBox_ItemList;

private:
	UPROPERTY()
	TSubclassOf<UUserWidget> BP_Slot;

	UPROPERTY()
	TArray<int> ItemIds;

	UPROPERTY()
	TArray<class UWidget_DroppedItemSlot*> Slots;

	UPROPERTY()
	class ADropItem* DropItem;

};
