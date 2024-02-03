// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolManager.h"
#include "../Interface/Poolable.h"

#pragma region Pool

void FPool::Init(UPoolable* Original, int count)
{
	// ���� ��ü�� �޾� �ش� ��ü�� ���� Pool Object ����
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
	// 1. Ǯ���� �ʿ��� ������Ʈ���� Pool�� �̸� ����� ����
}

void UPoolManager::Push(UPoolable* PoolObj)
{
	// Resource �Ŵ������� ������Ʈ�� Destroy �� �� ����
	// �˸��� PoolMap�� ������Ʈ�� �߰�
	// Ǯ ����� �� ���ִٸ� Resource �Ŵ������� ������Ʈ�� Ǯ������ �ʰ� �׳� �ı�
}

UObject* UPoolManager::Pop()
{
	// Resource �Ŵ������� ������Ʈ�� Spawn �� �� ����
	// Pool���� ������Ʈ�� �ϳ� ���� SetActive -> true
	// Ȥ�� Pool�� ����־ nullptr�� ���ҽ� �Ŵ����� ���� ������ �׳� Spawn �Լ��� ����
	return nullptr;
}

void UPoolManager::Clear()
{
	// Ǯ���� ��ü�� ��� �ı�
}

UObject* UPoolManager::GetfOriginal()
{
	// Ǯ(TMap)�� ���� ��ü ����
	return nullptr;
}

