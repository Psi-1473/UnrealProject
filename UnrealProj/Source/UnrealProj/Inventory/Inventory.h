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
	InventoryType GetType() { return Type; }
	TArray<class AItem*> GetInventory();

	void SetOwnerPlayer(class AMyPlayer* Player) { OwnerPlayer = Player; }
public:
	void GainItem(class AItem* Item);
//Test
	void ItemMake();

private:
	InventoryType Type;

	UPROPERTY()
	class AMyPlayer* OwnerPlayer;

	UPROPERTY()
	TArray<class AItem*> EquipItems;

	UPROPERTY()
	TArray<class AItem*> UseItems;

	UPROPERTY()
	TArray<class AItem*> EtcItems;

};
