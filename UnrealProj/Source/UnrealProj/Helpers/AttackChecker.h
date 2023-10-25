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
	// 1. Attacker is a player / Monster
	// 2. Attacker attacks directly in front / a specific location
	// Player
	static FHitResult PlayerCubeCheckSingle(FVector Range, float Start, ECollisionChannel TraceChannel, class AActor* Attacker);
	static TArray<FHitResult> PlayerCubeCheckMulti(FVector Range, float Start, ECollisionChannel TraceChannel, class AActor* Attacker);
	static TArray<FOverlapResult> PlayerCircleCheck(FVector SkillLocation, float Radius, float HalfHeight, ECollisionChannel TraceChannel, class AActor* Attacker);
	// Monster
	static TArray<FHitResult> MonsterCubeCheck(FVector Range, float Start, ECollisionChannel TraceChannel, class AActor* Attacker); // front
	static TArray<FHitResult> MonsterCubeCheck(FVector Range, FVector SkillLocation, ECollisionChannel TraceChannel, class AActor* Attacker); // a specific location
	static TArray<FOverlapResult> MonsterCircleCheck(FVector SkillLocation, float Radius, float HalfHeight, ECollisionChannel TraceChannel, class AActor* Attacker);

	static bool IsTargetInSectorForm(AActor* Attacker, AActor* HitActor, float Angle);

	// Draw Functions : For check Drawboxs during development
	static void DrawCubeHitBox(FVector StartVector, FVector EndVector, FVector RangeVector, float Start, AActor* Attacker, bool bHit);

	// Apply Damage : If you use a "Check Range Function" and have been returned FHitResult value, you can apply damage to Actor with these functions.
	static void ApplyHitDamageToActor(float Damage, class AActor* Attacker, FHitResult HitActor, AttackType AType = AttackType::NONE);
	static void ApplyHitDamageToActors(float Damage, class AActor* Attacker, TArray<FHitResult> HitActor, AttackType AType = AttackType::NONE, class UParticleSystem* Particle = nullptr);
	static void ApplyOverlapDamageToActors(float Damage, class AActor* Attacker, TArray<FOverlapResult> HitActor, class UParticleSystem* Particle = nullptr, AttackType AType = AttackType::NONE);

private:
	// FHitResult Ver
	static void ApplyPlayerDamageToMonster(float Damage, class AMyPlayer* Attacker, FHitResult HitActor); // 1명 공격

	static void ApplyPlayerDamageToMonster(float Damage, class AMyPlayer* Attacker, TArray<FHitResult> HitActor, class UParticleSystem* Particle); // 다수 공격
	static void ApplyMonsterDamageToPlayer(float Damage, class AMonster* Attacker, TArray<FHitResult> HitActor, AttackType AType); // 다수 공격

	// FOverlapResult Ver
	static void ApplyPlayerDamageToMonster(float Damage, class AMyPlayer* Attacker, TArray<FOverlapResult> HitActor, class UParticleSystem* Particle); // 다수 공격
	static void ApplyMonsterDamageToPlayer(float Damage, class AMonster* Attacker, TArray<FOverlapResult> HitActor, AttackType AType); // 다수

public:
	static void ApplyMonsterDamageToPlayerSectorForm(float Damage, class AMonster* Attacker, TArray<FOverlapResult> HitActor, AttackType AType, float Angle);
};
