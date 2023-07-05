// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Inventory.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_Inventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct();


private:
	void CreateSlot();
	void UpdateSlotInfo();

	UFUNCTION()
	void SetInventoryTypeEquip();
	UFUNCTION()
	void SetInventoryTypeUse();
	UFUNCTION()
	void SetInventoryTypeEtc();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Equip;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Use;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Etc;

	UPROPERTY(meta = (BindWidget))
	class UWrapBox* SlotBox;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_EquipWeapon;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_EquipTop;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_EquipPants;

	
	UPROPERTY()
	TArray<class UWidget_InvenSlot*> Slots;
};
