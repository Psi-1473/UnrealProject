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
	TWeakObjectPtr<class AMyPlayer> GetPlayer() { return OwnerPlayer; }
	TArray<class AItem*>& GetInventory();

	void SetType(InventoryType NewType) { Type = NewType; }
	void SetOwnerPlayer(TWeakObjectPtr<class AMyPlayer> Player) { OwnerPlayer = Player; }
public:
	void GainNewItem(class AItem* Item, int SlotIndex = -1); // SlotIndex�� �κ��丮 Ư�� ��ġ�� �ٷ� �������� �ִ��� Ȯ���ϱ� ���� ��� (ex. ������ �����ܼ� �ֱ�)
	void RemoveWeapon(int SlotIndex);
	void SwapItem(int DragedIndex, int ArrivedIndex);

private:
	void GainNewWeapon(class AWeapon* Item, int SlotIndex = -1);
	void GainNewUseItem(class AUseItem* Item, int SlotIndex = -1);

	int FindEmptySlotIndex(TArray<class AItem*>& ItemArray);
	int FindItem(TArray<class AItem*>& ItemArray, int Id);

private:
	InventoryType Type;
	
	
	UPROPERTY()
	TWeakObjectPtr<class AMyPlayer> OwnerPlayer;

	UPROPERTY()
	TArray<class AItem*> EquipItems;

	UPROPERTY()
	TArray<class AItem*> UseItems;

	UPROPERTY()
	TArray<class AItem*> EtcItems;

};
