// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../DEFINE.h"
#include "Components/RichTextBlockImageDecorator.h"
#include "Item.generated.h"

UCLASS()
class UNREALPROJ_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void UseItem(int SlotNumber);
	virtual void SetItemMesh();

	virtual FRichImageRow* GetItemImage(class UMyGameInstance* GInstance);
public:


	void SetId(int Value) { Id = Value; }
	void SetCount(int Value) { Count = Value; }
	void SetInventory(TWeakObjectPtr<class UInventory> Inven) { Inventory = Inven; }

	class UStaticMesh* GetStaticMesh() { return StaticMesh; }
	int GetCount() { return Count; }
	int GetId() { return Id; }
protected:
	UPROPERTY()
	int Id;

	UPROPERTY()
	int16 SlotIndex;

	UPROPERTY()
	TWeakObjectPtr<class UInventory> Inventory;

	UPROPERTY()
	int Count = 0;

	UPROPERTY()
	class UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;
};
