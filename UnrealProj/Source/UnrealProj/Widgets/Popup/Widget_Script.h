// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Script.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_Script : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void SetScript(TWeakObjectPtr<class ANpc> Npc);

	UFUNCTION()
	void PopupShopWidget();

	UFUNCTION()
	void PopupNpcQuestWidget();

	//UFUNCTION()
	//void PopupQuestWidget(TWeakObjectPtr<class ANpc>);

	UFUNCTION()
	void CloseUI();
	

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Script;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Shop;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Quest;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Exit;

	UPROPERTY()
	TWeakObjectPtr<class ANpc> OwnerNpc;
};
