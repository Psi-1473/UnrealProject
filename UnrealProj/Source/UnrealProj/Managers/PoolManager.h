// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interface/Poolable.h"
#include "UObject/NoExportTypes.h"
#include "PoolManager.generated.h"

/**
 * 
 */

#pragma region Pool

UCLASS()
class UNREALPROJ_API UPool : public UObject
{
	GENERATED_BODY()


public:
	void Init(UClass* Original, int count = 10);
	class AActor* Create();
	void Push(class AActor* PoolObj);
	AActor* Pop();

	UPROPERTY()
	UClass* OriginalObject;
	UPROPERTY()
	TArray<class AActor*> PoolQueue;
};
#pragma endregion Pool

UCLASS()
class UNREALPROJ_API UPoolManager : public UObject
{
	GENERATED_BODY()
	
public:
	UPoolManager();
	~UPoolManager();

	void Init();
	void CreatePool(UClass* Original, int count = 10);
	void Push(AActor* PoolObj);
	class AActor* Pop(FString ClassName);
	void Clear();
	bool IsPoolObject(FString ClassName);

private:
	// 풀링용 자료구조 만들기
	UPROPERTY()
	TMap<FString, UPool*> PoolMap;

	// Pooling Class
	TSubclassOf<class ADropItem> DropItem;

};
