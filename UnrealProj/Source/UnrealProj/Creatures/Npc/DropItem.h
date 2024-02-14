// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractObject.h"
#include "../../Interface/Poolable.h"
#include "DropItem.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API ADropItem : public AInteractObject, public IPoolable
{
	GENERATED_BODY()

public:
	void SetMiscItems(TArray<struct FMiscItemData*> Items) { MiscItems = Items; }
	void SetUseItems(TArray<struct FUseItemData*> Items) { UseItems = Items; }

public:
	virtual void Interact(class AMyPlayer* Player) override;
	

private:
	//TArray<struct FDropEquipmentsData*> MiscItems;
	TArray<struct FUseItemData*> UseItems;
	TArray<struct FMiscItemData*> MiscItems;
};
