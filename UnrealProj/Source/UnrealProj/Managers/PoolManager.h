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

USTRUCT()
struct FPool
{
	GENERATED_BODY()


public:
	void Init(class UPoolable* Original, int count);
	class UPoolable* Create();
	void Push(class UPoolable* PoolObj);
	void Pop();

	UPROPERTY()
	UObject* OriginalObject;
	UPROPERTY()
	TArray<class UPoolable*> PoolQueue;
};
#pragma endregion Pool

UCLASS()
class UNREALPROJ_API UPoolManager : public UObject
{
	GENERATED_BODY()
	
public:
	void Init();
	void Push(class UPoolable* PoolObj);
	UObject* Pop();
	void Clear();
	UObject* GetfOriginal();

private:
	// 풀링용 자료구조 만들기
	UPROPERTY()
	TMap<FString, FPool> Pool;
};
