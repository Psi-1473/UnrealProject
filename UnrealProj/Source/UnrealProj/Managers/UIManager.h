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
	int GetUiNumber() { return UiNumber; }
	UUserWidget* PopupUI(UWorld* World, UIType Type);
	void CloseUI(int Type);
	void CloseAllUI();
	void SetController(TWeakObjectPtr<class APlayerController> Controller) { PlayerController = Controller; }
	UUserWidget* GetUI(UIType Type) { return PopupUiArray[(int)Type]; }

public:
	UPROPERTY()
	int UiNumber = 0;

	TSubclassOf<UUserWidget> WidgetAsset;

	UPROPERTY()
	TWeakObjectPtr<class APlayerController> PlayerController;

	UPROPERTY()
	TArray<UUserWidget*> PopupUiArray;
};
