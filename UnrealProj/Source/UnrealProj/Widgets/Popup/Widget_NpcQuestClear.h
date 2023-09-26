// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_NpcQuestClear.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_NpcQuestClear : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;


	UFUNCTION()
		void CompleteQuest();

	void BindQuest(class UMyGameInstance* GInstance, TWeakObjectPtr<class ANpc> Npc, class UQuest* QuestData);
private:
	void ResetUI();

private:
	UPROPERTY()
	TWeakObjectPtr<class ANpc> OwnerNpc;

	UPROPERTY()
	class UQuest* Quest;


private:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_QuestTitle;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_QuestInfo;

	UPROPERTY(meta = (BindWidget))
		class UButton* Btn_Complete;

};
