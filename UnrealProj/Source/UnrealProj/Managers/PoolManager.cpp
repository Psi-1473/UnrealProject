// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolManager.h"
#include "../Creatures/Npc/DropItem.h"
#include "../Interface/Poolable.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

#pragma region Pool

void UPool::Init(UClass* Original, int count)
{
	// 원본 객체를 받아 해당 객체를 통해 Pool Object 생성
	OriginalObject = Original;
	for(int i = 0; i < count; i++)
		Push(Create());
}

AActor* UPool::Create()
{
	FWorldContext* world = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);

	FActorSpawnParameters Param;
	FRotator Rot;
	FVector SpawnLocation = FVector::ZeroVector;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* Actor = world->World()->SpawnActor<AActor>(OriginalObject, SpawnLocation, Rot, Param);
	Actor->SetActorHiddenInGame(true);

	return Actor;
}


void UPool::Push(AActor* PoolObj)
{
	PoolQueue.Push(PoolObj);
	Cast<AActor>(PoolObj)->SetActorHiddenInGame(true);
}

AActor* UPool::Pop()
{
	if(PoolQueue.Num() <= 0)
		return nullptr;
	AActor* PoolObj = PoolQueue.Pop();

	if(PoolObj != nullptr)
		return PoolObj;

	return nullptr;
}

#pragma endregion Pool

UPoolManager::UPoolManager()
{
	static ConstructorHelpers::FClassFinder<ADropItem> DROPITEM(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/InteractObj/DropItemPocket.DropItemPocket_C'"));
	if (DROPITEM.Succeeded()) DropItem = DROPITEM.Class;
}

UPoolManager::~UPoolManager()
{
}

void UPoolManager::Init()
{
	CreatePool(DropItem, 10);
}

void UPoolManager::CreatePool(UClass* Original, int count)
{
	UE_LOG(LogTemp, Warning, TEXT("Create New Pool! %s"), *Original->GetName());
	UPool* NewPool = NewObject<UPool>();
	NewPool->Init(Original, count);

	PoolMap.Add(Original->GetName(), NewPool);
}

void UPoolManager::Push(AActor* PoolObj)
{
	// Resource 매니저에서 오브젝트를 Destroy 할 때 실행
	// 알맞은 PoolMap에 오브젝트를 추가
	// 풀 사이즈가 꽉 차있다면 Resource 매니저에서 오브젝트를 풀링하지 않고 그냥 파괴
	FString Key = PoolObj->GetClass()->GetName();
	if (PoolMap.Contains(Key))
	{
		// 풀 사이즈 관련 추가할 것
		PoolMap[Key]->Push(PoolObj);
		PoolObj->SetActorHiddenInGame(true);
		PoolObj->SetActorLocation(FVector(0.f, 0.f, 0.f));
	}
}

AActor* UPoolManager::Pop(FString ClassName)
{
	// Resource 매니저에서 오브젝트를 Spawn 할 때 실행
	// Pool에서 오브젝트를 하나 꺼내 SetActive -> true
	// 혹시 Pool이 비어있어서 nullptr을 리소스 매니저가 리턴 받으면 그냥 Spawn 함수로 스폰
	if(PoolMap.Contains(ClassName))
		return (PoolMap[ClassName]->Pop());
	
	
	return nullptr;
}

void UPoolManager::Clear()
{
	// 풀링한 객체들 모두 파괴
}

bool UPoolManager::IsPoolObject(FString ClassName)
{
	if(PoolMap.Contains(ClassName))
		return true;
	else return false;
}

//AActor* UPoolManager::GetOriginal(FString ClassName)
//{
//	// 풀(TMap)의 원본 객체 리턴
//	if(PoolMap.Contains(ClassName))
//		return PoolMap[ClassName]->OriginalObject;
//	
//	return nullptr;
//}

