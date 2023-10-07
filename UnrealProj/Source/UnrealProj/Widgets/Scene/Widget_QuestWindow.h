// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_QuestWindow.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_QuestWindow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UWidget_QuestWindow(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION()
	void MinimizationWindow();

	void AddQuest(class UQuest* Data); // 퀘스트 클래스로 받을지 데이터로 받을지 ㄱㄷ
	void RemoveQuest(class UQuest* Data);

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Minimization;

	UPROPERTY(meta = (BindWidget))
	class UImage* BackGround_List;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ScrollBox_List;

	UPROPERTY()
	bool ListVisibility = true;

	UPROPERTY()
	TSubclassOf<UUserWidget> BP_Slot;

	UPROPERTY()
	TArray<class UWidget_QuestQuickInfo*> Slots;
};
