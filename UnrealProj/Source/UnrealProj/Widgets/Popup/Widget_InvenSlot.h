// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_InvenSlot.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_InvenSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Equip;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Use;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Etc;

	UPROPERTY(meta = (BindWidget))
	class UWrapBox* SlotBox;
	
};
