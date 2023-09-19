// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../DEFINE.h"
#include "AttackChecker.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UAttackChecker : public UObject
{
	GENERATED_BODY()

public:
	// "Check Range Functions" : Check if target is within a certain range
	// Shapes : Cube, Circle
	// if you choose circle shape, you can check if target is within a sector form with param(angle value)

	// Versions are divided by certain criteria
	// 1. Player Attack / Monster Attack
	// 2. Attacker attacks directly in front / a specific location
	static FHitResult PlayerCubeCheckSingle(FVector Range, float Start, ECollisionChannel TraceChannel, class AActor* Attacker);
	static TArray<FHitResult> PlayerCubeCheckMulti(FVector Range, float Start, ECollisionChannel TraceChannel, class AActor* Attacker);

	//Monster
	static TArray<FHitResult> MonsterCubeCheck(FVector Range, float Start, ECollisionChannel TraceChannel, class AActor* Attacker); // Attacker 정면
	static TArray<FHitResult> MonsterCubeCheck(FVector Range, FVector SkillLocation, ECollisionChannel TraceChannel, class AActor* Attacker); // 특정 위치에서 체크

	static TArray<FOverlapResult> MonsterCircleCheck(FVector SkillLocation, float Radius, float HalfHeight, ECollisionChannel TraceChannel, class AActor* Attacker);


	static bool IsTargetInSectorForm(AActor* Attacker, AActor* HitActor, float Angle);

	// Draw Functions : For check Drawboxs during development
	static void DrawCubeHitBox(FVector StartVector, FVector EndVector, FVector RangeVector, float Start, AActor* Attacker, bool bHit);

	// Apply Damage : If you use a "Check Range Functions" and have been returned FHitResult value, you can apply damage to Actor with these functions.
	static void ApplyHitDamageToActor(float Damage, class AActor* Attacker, FHitResult HitActor, AttackType AType = AttackType::NONE);
	static void ApplyHitDamageToActors(float Damage, class AActor* Attacker, TArray<FHitResult> HitActor, AttackType AType = AttackType::NONE);
	static void ApplyOverlapDamageToActors(float Damage, class AActor* Attacker, TArray<FOverlapResult> HitActor, AttackType AType = AttackType::NONE);

private:
	// FHitResult Ver
	static void ApplyPlayerDamageToMonster(float Damage, class AMyPlayer* Attacker, FHitResult HitActor); // 1명 공격

	static void ApplyPlayerDamageToMonster(float Damage, class AMyPlayer* Attacker, TArray<FHitResult> HitActor); // 다수 공격
	static void ApplyMonsterDamageToPlayer(float Damage, class AMonster* Attacker, TArray<FHitResult> HitActor, AttackType AType); // 다수 공격

	// FOverlapResult Ver
	static void ApplyPlayerDamageToMonster(float Damage, class AMyPlayer* Attacker, TArray<FOverlapResult> HitActor); // 다수 공격
	static void ApplyMonsterDamageToPlayer(float Damage, class AMonster* Attacker, TArray<FOverlapResult> HitActor, AttackType AType); // 다수

public:
	// Circle Check 함수로 식별한 Target이 부채꼴 안에 있는지 한 번 더 확인 후 데미지를 줄 때 사용
	static void ApplyMonsterDamageToPlayerSectorForm(float Damage, class AMonster* Attacker, TArray<FOverlapResult> HitActor, AttackType AType, float Angle);
};
