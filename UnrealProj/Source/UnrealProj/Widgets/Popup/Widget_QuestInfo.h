// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_QuestInfo.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_QuestInfo : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void SetQuestInfo(TWeakObjectPtr<class UWidget_Quest> Widget, class UQuest* Data);
	UFUNCTION()
	void ClickExitBtn();

private:
	UPROPERTY()
	TWeakObjectPtr<class UWidget_Quest> QuestWidget;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_QuickSlot; // 기능은 나중에 구현

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_GetDir; // 기능은 나중에 구현

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Exit;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_QuestTitle;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_QuestInfo;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_TargetMaxNum;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_TargetNowNum;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_TargetName;

};
