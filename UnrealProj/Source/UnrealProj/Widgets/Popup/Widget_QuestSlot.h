// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_QuestSlot.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_QuestSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void SetInfo(TWeakObjectPtr<class UWidget_Quest> Widget, class UQuest* QuestData);

	UFUNCTION()
	void PopupQuestInfoUI();

private:
	UPROPERTY()
	TWeakObjectPtr<class UWidget_Quest> QuestWidget;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_QuestName;

	UPROPERTY(meta = (BindWidget))
		class UButton* Btn_QuestName;

	UPROPERTY()
	class UQuest* Quest;
};
