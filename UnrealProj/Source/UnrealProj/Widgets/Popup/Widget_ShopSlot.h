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

	void SetSlot(class UMyGameInstance* GInstance, ItemType TemType, int16 Id);
private:
	class AWeapon* CreateNewWeapon();
	//AWeapon* CreateNewBow();
	class AUseItem* CreateNewUseItem();
private:
	ItemType IType;

	WEAPONTYPE WType;
	UPROPERTY()
	int16 ItemId;

	// 아이템 타입이랑 아이디로 나누지 말고
	// 변수를 그냥 AItem 객체로 가지자.

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Item;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Buy;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Gold;

};
