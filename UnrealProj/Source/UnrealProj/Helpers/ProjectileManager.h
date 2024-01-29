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
	// 필요한 정보
	// 1. SubObject 정보
	// 2. 투사체 속도
	// 3. 투사체 지속시간
	// 4. 투사체 포물선 그리는 정도
	static class AProjectile* FireProjectile(class AActor* Owner, TSubclassOf<class AProjectile> Obj, FVector StartLoc, FRotator Rot, float arcValue);
};
