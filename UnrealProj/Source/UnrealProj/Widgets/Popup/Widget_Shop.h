// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Shop.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_Shop : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct();

public:
	void SetOwnerNpc(TWeakObjectPtr<class ANpc> Npc) { OwnerNpc = Npc; }
	void CreateSlot(TWeakObjectPtr<class ANpc> Npc);


	UFUNCTION()
	void CloseUI();
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Exit;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* SlotBox;

	UPROPERTY()
	TWeakObjectPtr<class ANpc> OwnerNpc;
};
