// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_PlayerMain.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_PlayerMain : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void SwapSkillQuickSlot(int From, int To);
	void SwapItemQuickSlot(int From, int To);

private:
	void SetSkillQuick();
	void SetItemQuick();
	

private:
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* SkillBox;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* ItemBox;

	UPROPERTY()
	TArray<class UWidget_SkillQuick*> SkillQuickSlots;

	UPROPERTY()
	TArray<class UWidget_ItemQuick*> ItemQuickSlots;
	
};
