// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Quest.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_Quest : public UUserWidget
{
	GENERATED_BODY()

public:
	UWidget_Quest(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	void CreateSlot(class UPlayerQuestComponent* QuestComponent);
	void UpdateQuestInfo(class UQuest* QData);
	void SetOffInfoWidget();

	UFUNCTION()
	void SetListToOnGoingQuests();

	UFUNCTION()
	void SetListToCompleteQuests();

	UFUNCTION()
	void CloseUI();

private:
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ScrollBox_QuestList;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_OnGoing; //

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Complete;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Exit;

	UPROPERTY(meta = (BindWidget))
	class UWidget_QuestInfo* WBP_QuestInfo;
	UPROPERTY()
	TSubclassOf<UUserWidget> BP_Slot;

};
