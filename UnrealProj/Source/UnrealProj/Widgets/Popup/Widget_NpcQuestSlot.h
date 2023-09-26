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
	void Init(TWeakObjectPtr<class ANpc> Npc, FQuestData* NewQuestData);
	void Init(TWeakObjectPtr<class ANpc> Npc, class UQuest* NewQuestData);
	void SetCompletable(bool Value) { bCompletable = Value; }
	UFUNCTION()
	void PopupQuestLineScript();
private:
	UPROPERTY()
	TWeakObjectPtr<class ANpc> OwnerNpc;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_QuestName;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_ClearMark;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_QuestName;

	UPROPERTY()
	FQuestData QuestData;

	UPROPERTY()
	class UQuest* QuestDataClass;

	UPROPERTY()
	bool bCompletable;
	
}; 
