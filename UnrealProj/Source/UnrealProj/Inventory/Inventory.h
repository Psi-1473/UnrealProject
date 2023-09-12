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
	TArray<class AItem*>& GetUseItems() { return UseItems; }
	TArray<class AItem*>& GetEtcItems() { return UseItems; }
	TArray<class AItem*>& GetWeaponItems() { return UseItems; }
	int GetGold() { return Gold; }

	void SetType(InventoryType NewType) { Type = NewType; }
	void SetOwnerPlayer(TWeakObjectPtr<class AMyPlayer> Player) { OwnerPlayer = Player; }
	
public:
	void GainNewItem(ItemType IType, int Id, int SlotIndex = -1); // SlotIndex는 인벤토리 특정 위치에 바로 아이템을 넣는지 확인하기 위해 사용 (ex. 아이템 끌어당겨서 넣기)
	void EmptySlot(TArray<class AItem*>& ItemArray, int Index);
	void SwapItem(int DragedIndex, int ArrivedIndex);
	void AddGold(int Value);
private:
	void GainNewWeapon(class AItem* Item, int SlotIndex = -1);
	void GainNewUseItem(class AItem* Item, int SlotIndex = -1);

	class AWeapon* CreateWeapon(int Id, WEAPONTYPE WType);
	class AUseItem* CreateUseItem(int Id);


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

	UPROPERTY()
	int Gold = 5000;

};
