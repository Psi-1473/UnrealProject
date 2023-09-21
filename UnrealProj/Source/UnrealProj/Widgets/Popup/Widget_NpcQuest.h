// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_NpcQuest.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_NpcQuest : public UUserWidget
{
	GENERATED_BODY()
public:
	UWidget_NpcQuest(const FObjectInitializer& ObjectInitializer);

public:
	void BindAndCreateSlot(class UQuestComponent* QuestComp);
	void UpdateInfo(struct FQuestData Data);

private:
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ScrollBox_QuestList;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_QuestTitle;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_QuestInfo;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Okay;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Exit;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Okay;
private:
	UPROPERTY()
	int32 SelectedQuestId = -1;
	UPROPERTY()
	TWeakObjectPtr<class UQuestComponent> QuestComponent;

	UPROPERTY()
	TSubclassOf<UUserWidget> BP_Slot;

	
	
};
