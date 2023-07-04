// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../DEFINE.h"

/**
 * 
 */
class UNREALPROJ_API UIManager
{
public:
	UIManager();
	~UIManager();

	UUserWidget* PopupUI(UWorld* World, UIType Type);
	void CloseUI(UIType Type);
	void SetController(TWeakObjectPtr<class APlayerController> Controller) { PlayerController = Controller; }

public:
	int UiNumber = 0;
	TSubclassOf<UUserWidget> WidgetAsset;

	UPROPERTY()
	TWeakObjectPtr<class APlayerController> PlayerController;

	UPROPERTY()
	TArray<UUserWidget*> PopupUiArray;
};
