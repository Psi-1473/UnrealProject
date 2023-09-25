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
	virtual void NativeConstruct() override;

	void BindAndCreateSlot(TWeakObjectPtr<class ANpc> Npc);
	void SetOwnerNpc(TWeakObjectPtr<class ANpc> Npc) { OwnerNpc = Npc; }

private:
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ScrollBox_QuestList;





	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Exit;

private:
	UPROPERTY()
	TWeakObjectPtr<class ANpc> OwnerNpc;

	UPROPERTY()
	int32 SelectedQuestId = -1;
	UPROPERTY()
	TWeakObjectPtr<class UQuestComponent> QuestComponent;
	// 엔피씨 정보를 받아와야겠구나

	UPROPERTY()
	TSubclassOf<UUserWidget> BP_Slot;

	UPROPERTY()
	TArray<class UUserWidget*> Slots;

	
	
};
