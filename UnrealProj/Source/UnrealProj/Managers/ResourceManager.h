// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interface/Poolable.h"
#include "UObject/NoExportTypes.h"
#include "ResourceManager.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UResourceManager : public UObject
{
	GENERATED_BODY()
	
public:
	// 이름 Load 로 바꾸기
	template<class T>
	inline T* Load(FString Dir)
	{
		// 오브젝트 풀링이 가능한 지 판단 후 가능하다면 풀링
		UE_LOG(LogTemp, Warning, TEXT("Class Name %s"), *(T::StaticClass()->GetName()));
		return (T*)LoadObject<T>(NULL, *Dir, NULL, LOAD_None, NULL);
	}

	template<class T>
	inline void Instantiate(FString Dir)
	{

	}

	void Destroy()
	{

	}

};
