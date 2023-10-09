// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InteractObjManager.generated.h"

/**
 * 
 */

USTRUCT()
struct FLootObj
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere)
	TArray<class ALootObject*> LootObjs;
};


UCLASS()
class UNREALPROJ_API UInteractObjManager : public UObject
{
	GENERATED_BODY()

public:
	void AddLootObject(class ALootObject* Obj);

	void MakeObjVisible(int Id);
	void MakeObjInvisible(int Id);


private:
	UPROPERTY()
	TMap<int32, FLootObj> InterObjects;
};