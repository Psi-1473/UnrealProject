// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Revive.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_Revive : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void SetPlayer(class AMyPlayer* PlayerValue);

	UFUNCTION()
	void ClickRevive();

private:
	UPROPERTY()
	class AMyPlayer* Player;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Revive;


};
