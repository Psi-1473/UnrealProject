// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../DEFINE.h"
#include "Widget_ShopSlot.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_ShopSlot : public UUserWidget
{
	GENERATED_BODY()
	

public:
	void ClickBuyButton();
private:
	InventoryType Type;

	UPROPERTY()
	int16 ItemId;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Buy;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Gold;

};
