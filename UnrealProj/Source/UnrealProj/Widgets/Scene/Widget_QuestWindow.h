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
	virtual void NativeConstruct() override;
	UFUNCTION()
	void MinimizationWindow();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Minimization;

	UPROPERTY(meta = (BindWidget))
	class UImage* BackGround_List;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ScrollBox_List;
};
