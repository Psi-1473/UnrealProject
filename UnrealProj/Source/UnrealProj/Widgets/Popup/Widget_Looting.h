// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Looting.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_Looting : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	void SetTime(float Value, TWeakObjectPtr<class ALootObject> Obj);
private:
	UPROPERTY()
	int Id;

	UPROPERTY()
	float GoalTime = 0;

	UPROPERTY()
	float PrevTime;

	UPROPERTY()
	TWeakObjectPtr<class ALootObject> LootObj;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Bar;
};
