// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolManager.h"
#include "../Creatures/Npc/DropItem.h"
#include "../Interface/Poolable.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

#pragma region Pool

void UPool::Init(UClass* Original, int count)
{
	// ���� ��ü�� �޾� �ش� ��ü�� ���� Pool Object ����
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
	// Resource �Ŵ������� ������Ʈ�� Destroy �� �� ����
	// �˸��� PoolMap�� ������Ʈ�� �߰�
	// Ǯ ����� �� ���ִٸ� Resource �Ŵ������� ������Ʈ�� Ǯ������ �ʰ� �׳� �ı�
	FString Key = PoolObj->GetClass()->GetName();
	if (PoolMap.Contains(Key))
	{
		// Ǯ ������ ���� �߰��� ��
		PoolMap[Key]->Push(PoolObj);
		PoolObj->SetActorHiddenInGame(true);
		PoolObj->SetActorLocation(FVector(0.f, 0.f, 0.f));
	}
}

AActor* UPoolManager::Pop(FString ClassName)
{
	// Resource �Ŵ������� ������Ʈ�� Spawn �� �� ����
	// Pool���� ������Ʈ�� �ϳ� ���� SetActive -> true
	// Ȥ�� Pool�� ����־ nullptr�� ���ҽ� �Ŵ����� ���� ������ �׳� Spawn �Լ��� ����
	if(PoolMap.Contains(ClassName))
		return (PoolMap[ClassName]->Pop());
	
	
	return nullptr;
}

void UPoolManager::Clear()
{
	// Ǯ���� ��ü�� ��� �ı�
}

bool UPoolManager::IsPoolObject(FString ClassName)
{
	if(PoolMap.Contains(ClassName))
		return true;
	else return false;
}

//AActor* UPoolManager::GetOriginal(FString ClassName)
//{
//	// Ǯ(TMap)�� ���� ��ü ����
//	if(PoolMap.Contains(ClassName))
//		return PoolMap[ClassName]->OriginalObject;
//	
//	return nullptr;
//}

