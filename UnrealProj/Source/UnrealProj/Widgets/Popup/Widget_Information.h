// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <UnrealProj/DEFINE.h>
#include "Widget_Information.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_Information : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetInfoByItem(InformationType Type, class AItem* Item);
	void SetInfoBySkill(class USkill* Skill);
	void SetPosition(FVector2D Pos);

private:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_Sub;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Value;
};
