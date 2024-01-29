// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProjectileManager.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UProjectileManager : public UObject
{
	GENERATED_BODY()

public:
	// �ʿ��� ����
	// 1. SubObject ����
	// 2. ����ü �ӵ�
	// 3. ����ü ���ӽð�
	// 4. ����ü ������ �׸��� ����
	static class AProjectile* FireProjectile(class AActor* Owner, TSubclassOf<class AProjectile> Obj, FVector StartLoc, FRotator Rot, float arcValue);
};
