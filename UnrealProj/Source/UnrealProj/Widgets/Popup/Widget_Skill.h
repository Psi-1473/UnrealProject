// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Skill.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_Skill : public UUserWidget
{
	GENERATED_BODY()
public:
	UWidget_Skill(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void SetSwordSkill();
	UFUNCTION()
	void SetBowSkill();

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* Btn_Exit;

	UPROPERTY(meta = (BindWidget))
		class UHorizontalBox* WidgetBox;

	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Sword;

	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Bow;

	//UPROPERTY()
	//TArray<class UWidget_SkillSlot*> Slots;
	
	UPROPERTY()
	TSubclassOf<UUserWidget> BP_SwordSkill;

	UPROPERTY()
	TSubclassOf<UUserWidget> BP_BowSkill;



};
