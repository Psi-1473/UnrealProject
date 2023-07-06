// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../DEFINE.h"
#include "Blueprint/DragDropOperation.h"
#include "DragWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UDragWidget : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere)
	int SlotIndex;

	UPROPERTY(EditAnyWhere)
	class AItem* SlotItem;
	
};
