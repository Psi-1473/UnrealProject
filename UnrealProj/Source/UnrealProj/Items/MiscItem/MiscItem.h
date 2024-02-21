// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item.h"
#include "MiscItem.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AMiscItem : public AItem
{
	GENERATED_BODY()
	
public:
	virtual void SetCount(int Value);
	virtual void LoadItemData(class UMyGameInstance* GInstance) {};

	virtual FRichImageRow* GetItemImage(class UMyGameInstance* GInstance) override;
};
