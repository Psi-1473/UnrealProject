// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../MyGameInstance.h"
#include "Widget_LineScript.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_LineScript : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	void BindQuestScript(class UMyGameInstance* GInstance, TWeakObjectPtr<class ANpc> Npc, int32 BindQuestId);

	UFUNCTION()
	void OpenFollowingLine();
	
private:
	void UpdateLine(int Page);
private:
	// 나중에 Script Type을 추가할 것
	// Quest Script 인지 다른지에 따라 OpenFollowingLine 종료시 실행할 함수 설정
	UPROPERTY()
	TWeakObjectPtr<class ANpc> OwnerNpc;

	UPROPERTY()
	int32 QuestId;
	UPROPERTY()
	int32 NextPage = 1;

	UPROPERTY()
	class UDataTable* Script;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Script;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Next;

	//UPROPERTY()
	//TWeakObjectPtr<class ANpc> OwnerNpc;
};
