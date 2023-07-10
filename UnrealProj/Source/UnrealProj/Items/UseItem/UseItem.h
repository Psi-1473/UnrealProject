// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item.h"
#include "UseItem.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AUseItem : public AItem
{
	GENERATED_BODY()
public:
	AUseItem();

public:
	virtual void UseItem() override;
	virtual void SetItemMesh() override;
	virtual void SetCount(int Value);
	

	virtual FRichImageRow* GetItemImage(class UMyGameInstance* GInstance) override;

	void SetUseType(int Value) { UseType = Value; }
	void SetAmount(int Value) { Amount = Value; }
private:
	UPROPERTY()
	int UseType;

	UPROPERTY()
	int Amount;
};
