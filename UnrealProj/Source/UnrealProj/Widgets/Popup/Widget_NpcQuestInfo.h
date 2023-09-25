// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_NpcQuestInfo.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_NpcQuestInfo : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;


	UFUNCTION()
	void TakeQuest();

	UFUNCTION()
	void RefuseQuest();

	void BindQuest(class UMyGameInstance* GInstance, TWeakObjectPtr<class ANpc> Npc, int32 BindQuestId);
private:
	void ResetUI();
private:
	UPROPERTY()
	TWeakObjectPtr<class ANpc> OwnerNpc;

	UPROPERTY()
	int32 QuestId;

private:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_QuestTitle;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_QuestInfo;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Okay;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Refuse;


};
