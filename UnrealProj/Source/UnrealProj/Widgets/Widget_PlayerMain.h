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
	void SwapSkillQuickSlot(class UPlayerSkillComponent* SkillComponent, int From, int To);
	void SwapItemQuickSlot(int From, int To);

	void PressQuickSlot(int Index);
	void EmptyItemSlot(int Index);
	void RefreshItemQuickSlot(int Index);

	void BindPlayer(class UPlayerStatComponent* StatComp);
private:
	void SetSkillQuick();
	void SetItemQuick();
	
	void UpdateHpBar();
	void UpdateMpBar();
	void UpdateExpBar();

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Hp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Mp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Exp;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* SkillBox;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* ItemBox;

	UPROPERTY()
	TArray<class UWidget_SkillQuick*> SkillQuickSlots;

	UPROPERTY()
	TArray<class UWidget_ItemQuick*> ItemQuickSlots;
	
	UPROPERTY()
	TWeakObjectPtr<class UPlayerStatComponent> PlayerStatComp;
	
};
