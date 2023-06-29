// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../DEFINE.h"
#include "Inventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJ_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventory();

protected:
	virtual void BeginPlay() override;

public:
	void GainItem();
	

private:
	//UPROPERTY()
	//TArray<Item> EquipItems;
	//
	//UPROPERTY()
	//TArray<Item> UseItems;
	//
	//UPROPERTY()
	//TArray<Item> EtcItems;

};
