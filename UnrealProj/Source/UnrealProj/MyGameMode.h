// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMyGameMode();
	UUserWidget* GetCurrentWidget() { return CurrentWidget; }

	void BindPlayer(class AMyPlayer* Player);


private:
	UPROPERTY(VisibleAnywhere)
		TSubclassOf<UUserWidget> HUD_Class;

	UPROPERTY(VisibleAnywhere)
		UUserWidget* CurrentWidget;
};
