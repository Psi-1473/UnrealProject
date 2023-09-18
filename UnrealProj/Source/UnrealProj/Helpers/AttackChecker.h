// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AttackChecker.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UAttackChecker : public UObject
{
	GENERATED_BODY()

public:
	// Check Functions
	// 플레이어 체크, 몬스터 체크 따로 pirvate에 두고 HitCheck 자체를 만들어(public) 그 함수 하나로만 실행하게 지금은 테스트 용이라 걍 플레이어만
	// public으로
	static FHitResult PlayerCubeCheckSingle(FVector Range, float Start, ECollisionChannel TraceChannel, class AActor* Attacker);
	static TArray<FHitResult> PlayerCubeCheckMulti(FVector Range, float Start, ECollisionChannel TraceChannel, class AActor* Attacker);

	// Draw Functions
	static void DrawCubeHitBox(FVector StartVector, FVector EndVector, class AActor* Attacker);

	// Apply Damage
	static void ApplyDamageToActor(class AActor* Attacker, FHitResult HitActor);
	static void ApplyDamageToActors(class AActor* Attacker, TArray<FHitResult> HitActor);

private:
	static void ApplyPlayerDamageToMonster(class AMyPlayer* Attacker, FHitResult HitActor);
	static void ApplyPlayerDamageToMonster(class AMyPlayer* Attacker, TArray<FHitResult> HitActor);

	
};
