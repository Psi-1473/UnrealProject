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

	virtual void UseItem();
	virtual void SetItemMesh(int _Id, WEAPONTYPE _Type = WEAPON_END);

	virtual FRichImageRow* GetItemImage(class UMyGameInstance* GInstance);
public:
	void SetId(int Value) { Id = Value; }
	void SetCount(int Value) { Count = Value; }
	void SetOwnerPlayer(class AMyPlayer* Player) { OwnerPlayer = Player; }

	class UStaticMesh* GetStaticMesh() { return StaticMesh; }
	int GetCount() { return Count; }

protected:
	UPROPERTY()
	int Id;

	UPROPERTY()
	class AMyPlayer* OwnerPlayer;

	UPROPERTY()
	int Count = 0;

	UPROPERTY()
	class UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;
};
