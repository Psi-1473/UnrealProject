// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interface/Poolable.h"
#include "../MyGameInstance.h"
#include "PoolManager.h"
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
	void SetInstance(UMyGameInstance* Instance) { GInstance = Instance; }
public:
	// �̸� Load �� �ٲٱ�
	template<class T>
	inline T* Load(FString Dir)
	{
		UE_LOG(LogTemp, Warning, TEXT("Class Name %s"), *(T::StaticClass()->GetName()));
		return (T*)LoadObject<T>(NULL, *Dir, NULL, LOAD_None, NULL);
	}

	template<class T>
	inline T* Instantiate(const FString Dir, AActor* Owner, FVector Location, FRotator Rotation)
	{
		// Ǯ���Ȱ� �ִ°� Ȯ��
		auto PoolObject = GInstance->GetPoolMgr()->Pop(GetClassNameFromDir(Dir));
		if (PoolObject != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Pooling (O) : %s"), *PoolObject->GetName());

			PoolObject->SetActorHiddenInGame(false);
			PoolObject->SetActorLocation(Location);
			PoolObject->SetActorRotation(Rotation);

			return Cast<T>(PoolObject);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Pooling (X)"));
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = Owner;
			SpawnParams.Instigator = Owner->GetInstigator();
			auto Obj = LoadClass<T>(NULL, *Dir, NULL, LOAD_None, NULL);
			UE_LOG(LogTemp, Warning, TEXT("Class Name %s"), *(Obj->GetName()));
			return Owner->GetWorld()->SpawnActor<T>(Obj, Location, Rotation, SpawnParams);
		}

		
	}
	template<class T>
	inline T* Instantiate(TSubclassOf<T> ObjectClass, AActor* Owner, FVector Location, FRotator Rotation)
	{
	
		if (ObjectClass.Get()->ImplementsInterface(UPoolable::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Pooling (O)"));
			/*
				auto PoolObject = GInstance->GetPoolMgr()->Pop(GetClassNameFromDir(Dir));
			if (PoolObject != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Pooling (O)"));
				PoolObject->SetActorLocation(Location);
				PoolObject->SetActorRotation(Rotation);
				PoolObject->SetActorHiddenInGame(false);
			}
			*/
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Pooling (X)"));
			// �ؿ��ִ� Spawn �ڵ� �ű��
		}


		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Owner;
		SpawnParams.Instigator = Owner->GetInstigator();

		return Owner->GetWorld()->SpawnActor<T>(ObjectClass, Location, Rotation, SpawnParams);

	}

	template<class T>
	void Destroy(AActor* Object)
	{
		if (Object->GetClass()->ImplementsInterface(UPoolable::StaticClass()))
		{
			// Ǯ�� ������ ��ü�� Ǯ��
			UE_LOG(LogTemp, Warning, TEXT("Possible Pooling, Push to Pool"));
			GInstance->GetPoolMgr()->Push(Object);
		}
		else
		{
			// Ǯ�� �Ұ����ϸ� �ı�
			UE_LOG(LogTemp, Warning, TEXT("Impossible Pooling, Just Destroy"));
			Object->Destroy();
		}
	}

	FString GetClassNameFromDir(FString Dir);

private:
	UMyGameInstance* GInstance;
};
