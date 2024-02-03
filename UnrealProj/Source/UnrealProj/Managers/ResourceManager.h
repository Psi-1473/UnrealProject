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
	// �̸� Load �� �ٲٱ�
	template<class T>
	inline T* Load(FString Dir)
	{
		// ������Ʈ Ǯ���� ������ �� �Ǵ� �� �����ϴٸ� Ǯ��
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
