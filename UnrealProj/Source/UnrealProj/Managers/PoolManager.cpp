// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolManager.h"
#include "../Interface/Poolable.h"

#pragma region Pool

void FPool::Init(UPoolable* Original, int count)
{
	// 원본 객체를 받아 해당 객체를 통해 Pool Object 생성
}

UPoolable* FPool::Create()
{
	return nullptr;
}

void FPool::Push(UPoolable* PoolObj)
{
}

void FPool::Pop()
{
}

#pragma endregion Pool

void UPoolManager::Init()
{
	// 1. 풀링이 필요한 오브젝트들의 Pool을 미리 만들어 놓기
}

void UPoolManager::Push(UPoolable* PoolObj)
{
	// Resource 매니저에서 오브젝트를 Destroy 할 때 실행
	// 알맞은 PoolMap에 오브젝트를 추가
	// 풀 사이즈가 꽉 차있다면 Resource 매니저에서 오브젝트를 풀링하지 않고 그냥 파괴
}

UObject* UPoolManager::Pop()
{
	// Resource 매니저에서 오브젝트를 Spawn 할 때 실행
	// Pool에서 오브젝트를 하나 꺼내 SetActive -> true
	// 혹시 Pool이 비어있어서 nullptr을 리소스 매니저가 리턴 받으면 그냥 Spawn 함수로 스폰
	return nullptr;
}

void UPoolManager::Clear()
{
	// 풀링한 객체들 모두 파괴
}

UObject* UPoolManager::GetfOriginal()
{
	// 풀(TMap)의 원본 객체 리턴
	return nullptr;
}

