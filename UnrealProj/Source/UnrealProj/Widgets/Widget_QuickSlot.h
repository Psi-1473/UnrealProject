// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_QuickSlot.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_QuickSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	class UTextBlock* GetTextKey() { return Text_Key; }

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Object;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Key;

	
};
