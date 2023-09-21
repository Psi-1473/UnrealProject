// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../MyGameInstance.h"
#include "Widget_NpcQuestSlot.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_NpcQuestSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void Init(class UWidget_NpcQuest* QWidget, struct FQuestData* QData);
	void PopupQuestLineScript();
	UFUNCTION()
	void UpdateQuestInfo();
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_QuestName;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_QuestName;

	UPROPERTY()
	TWeakObjectPtr<class UWidget_NpcQuest> QuestWidget;

	UPROPERTY()
	FQuestData QuestData;
	
}; 
