// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackChecker.h"
#include "Kismet/GameplayStatics.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../Creatures/Monster/Monster.h"
#include "Engine/DamageEvents.h"
#include "Components/AudioComponent.h"
#include "../Items/Weapons/Weapon.h"
#include "Particles/ParticleSystem.h"

#pragma region CheckRange Functions
// Range - (X = Side, Y = Up, Z = Front)
FHitResult UAttackChecker::PlayerCubeCheckSingle(FVector Range, float Start, ECollisionChannel TraceChannel, AActor* Attacker)
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, Attacker);

	FVector StartVector = Attacker->GetActorLocation() + Attacker->GetActorForwardVector() * Start;
	FVector EndVector = Attacker->GetActorLocation() + Attacker->GetActorForwardVector() * (Range.Z + Start);

	bool bResult = Attacker->GetWorld()->SweepSingleByChannel(
		OUT HitResult,
		StartVector,
		EndVector,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel5,
		FCollisionShape::MakeBox(Range),//측면, 높이, 정면
		Params);

	
	return HitResult;
}

TArray<FHitResult> UAttackChecker::PlayerCubeCheckMulti(FVector Range, float Start, ECollisionChannel TraceChannel, AActor* Attacker)
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params(NAME_None, false, Attacker);

	FVector StartVector = Attacker->GetActorLocation() + Attacker->GetActorForwardVector() * Start;
	FVector EndVector = Attacker->GetActorLocation() + Attacker->GetActorForwardVector() * (Range.Z + Start);

	bool bResult = Attacker->GetWorld()->SweepMultiByChannel(
		OUT HitResults,
		StartVector,
		EndVector,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel5,
		FCollisionShape::MakeBox(Range),//측면, 높이, 정면
		Params);

	return HitResults;
}

TArray<FOverlapResult> UAttackChecker::PlayerCircleCheck(FVector SkillLocation, float Radius, float HalfHeight, ECollisionChannel TraceChannel, AActor* Attacker)
{
	FTransform Trans = Attacker->GetActorTransform();
	// 히트 체크
	FCollisionQueryParams Params(NAME_None, false, Attacker);
	TArray<FOverlapResult> OutOverlaps;

	Attacker->GetWorld()->OverlapMultiByChannel(
		OutOverlaps,
		Attacker->GetActorLocation(),
		FQuat::Identity,
		TraceChannel,
		FCollisionShape::MakeCapsule(Radius, HalfHeight),
		Params);

	return OutOverlaps;
}

TArray<FHitResult> UAttackChecker::MonsterCubeCheck(FVector Range, float Start, ECollisionChannel TraceChannel, AActor* Attacker)
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params(NAME_None, false, Attacker);

	FVector StartVector = Attacker->GetActorLocation() + Attacker->GetActorForwardVector() * Start;
	FVector EndVector = Attacker->GetActorLocation() + Attacker->GetActorForwardVector() * (Range.Z + Start);

	Attacker->GetWorld()->SweepMultiByChannel(
		OUT HitResults,
		StartVector,
		EndVector,
		FQuat::Identity,
		TraceChannel,
		FCollisionShape::MakeBox(Range),
		Params);
	return HitResults;
}

TArray<FHitResult> UAttackChecker::MonsterCubeCheck(FVector Range, FVector SkillLocation, ECollisionChannel TraceChannel, AActor* Attacker)
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params(NAME_None, false, Attacker);

	 Attacker->GetWorld()->SweepMultiByChannel(
		OUT HitResults,
		SkillLocation,
		SkillLocation + Attacker->GetActorForwardVector() * Range.X,
		FQuat::Identity,
		TraceChannel,
		FCollisionShape::MakeBox(Range),
		Params);


	return HitResults;
}

TArray<FOverlapResult> UAttackChecker::MonsterCircleCheck(FVector SkillLocation, float Radius, float HalfHeight, ECollisionChannel TraceChannel, AActor* Attacker)
{
	FTransform Trans = Attacker->GetActorTransform();
	// 히트 체크
	FCollisionQueryParams Params(NAME_None, false, Attacker);
	TArray<FOverlapResult> OutOverlaps;

	Attacker->GetWorld()->OverlapMultiByChannel(
		OutOverlaps,
		Attacker->GetActorLocation(),
		FQuat::Identity,
		TraceChannel,
		FCollisionShape::MakeCapsule(Radius, HalfHeight),
		Params);

	return OutOverlaps;
}

bool UAttackChecker::IsTargetInSectorForm(AActor* Attacker, AActor* TargetActor, float Angle)
{
	FVector FirstVector = Attacker->GetActorForwardVector();
	FVector SecondVector = TargetActor->GetActorLocation() - (Attacker->GetActorLocation() - Attacker->GetActorForwardVector() * 40);

	float SizeMul = FirstVector.Size() * SecondVector.Size();
	float DegreeBetween = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(FirstVector, SecondVector) / SizeMul));
	UE_LOG(LogTemp, Warning, TEXT("Skill Angle : %f, Target To Hiter Angle : %f"), Angle, DegreeBetween);
	if (DegreeBetween <= Angle / 2.0f)
		return true;

	return false;
}

#pragma endregion

#pragma region Draw Functions
void UAttackChecker::DrawCubeHitBox(FVector StartVector, FVector EndVector, FVector RangeVector, float Start, AActor* Attacker, bool bHit)
{
	FVector Vec = Attacker->GetActorForwardVector() * Start;
	FVector Center = StartVector + (EndVector - StartVector) / 2;
	FQuat Rotation = FRotationMatrix::MakeFromZ(Vec).ToQuat();
	FColor DrawColor;
	if (bHit)
		DrawColor = FColor::Green;
	else
		DrawColor = FColor::Red;

	DrawDebugBox(Attacker->GetWorld(), Center, RangeVector, Rotation, DrawColor, false, 2.f);

}

#pragma endregion

#pragma region Apply Damage Functions


void UAttackChecker::ApplyHitDamageToActor(float Damage, AActor* Attacker, FHitResult HitActor, AttackType AType)
{
	auto Player = Cast<AMyPlayer>(Attacker);

	if (Player)
		ApplyPlayerDamageToMonster(Damage, Player, HitActor);
}
void UAttackChecker::ApplyHitDamageToActors(float Damage, AActor* Attacker, TArray<FHitResult> HitActors, AttackType AType, UParticleSystem* Particle)
{
	auto Player = Cast<AMyPlayer>(Attacker);
	auto Monster = Cast<AMonster>(Attacker);
	if (Player)
		ApplyPlayerDamageToMonster(Damage, Player, HitActors, Particle);
	else if (Monster)
		ApplyMonsterDamageToPlayer(Damage, Monster, HitActors, AType);
}
void UAttackChecker::ApplyOverlapDamageToActors(float Damage, AActor* Attacker, TArray<FOverlapResult> HitActors, UParticleSystem* Particle, AttackType AType)
{
	auto Player = Cast<AMyPlayer>(Attacker);
	auto Monster = Cast<AMonster>(Attacker);
	if (Player)
		ApplyPlayerDamageToMonster(Damage, Player, HitActors, Particle);
	else if (Monster)
		ApplyMonsterDamageToPlayer(Damage, Monster, HitActors, AType);
}

void UAttackChecker::ApplyPlayerDamageToMonster(float Damage, AMyPlayer* Attacker, FHitResult HitActor)
{
	if (HitActor.GetActor() == nullptr)//이거 지워도 되나?
		return;

	auto Monster = Cast<AMonster>(HitActor.GetActor());

	if (Monster == nullptr)
		return;

	UE_LOG(LogTemp, Log, TEXT("Hit Actor : %s"), *HitActor.GetActor()->GetName());
	FDamageEvent DamageEvent;;
	Monster->TakeDamage(10.f, DamageEvent, Attacker->GetController(), Attacker); //Temp
	Monster->PlaySoundWave(Monster->GetAudioComponent(), Attacker->GetWeapon()->GetHitSound());
}

void UAttackChecker::ApplyPlayerDamageToMonster(float Damage, AMyPlayer* Attacker, TArray<FHitResult> HitActors, UParticleSystem* Particle)
{
	if (HitActors.IsEmpty())//이거 지워도 되나?
		return;


	for (FHitResult HitResult : HitActors)
	{
		UE_LOG(LogTemp, Log, TEXT("ATTACK CHECKER - Hit Actor : %s"), *HitResult.GetActor()->GetName());
		AMonster* Enemy = Cast<AMonster>(HitResult.GetActor());
		FDamageEvent DamageEvent;
		if (Enemy == nullptr)
			return;
		Enemy->OnDamaged(Damage, DamageEvent, Attacker->GetController(), Attacker, Particle); //Temp
		Enemy->PlaySoundWave(Enemy->GetAudioComponent(), Attacker->GetWeapon()->GetHitSound());
	}
}
void UAttackChecker::ApplyMonsterDamageToPlayer(float Damage, AMonster* Attacker, TArray<FHitResult> HitActor, AttackType AType)
{
	if (HitActor.IsEmpty())//이거 지워도 되나?
		return;

	for (FHitResult HitResult : HitActor)
	{
		UE_LOG(LogTemp, Log, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());
		AMyPlayer* Player = Cast<AMyPlayer>(HitResult.GetActor());
		auto Monster = Cast<AMonster>(Attacker);
		FDamageEvent DamageEvent;
		
		if (Player == nullptr || Monster == nullptr)
			return;

		if (Monster->GetDeath() == true)
			return;

		Player->OnDamaged(Damage, DamageEvent, Monster->GetController(), Attacker, AType); //Temp
		// 소리재생
		
	}
}
void UAttackChecker::ApplyPlayerDamageToMonster(float Damage, AMyPlayer* Attacker, TArray<FOverlapResult> HitActors, UParticleSystem* Particle)
{
	if (HitActors.IsEmpty())//이거 지워도 되나?
		return;


	for (FOverlapResult HitResult : HitActors)
	{
		UE_LOG(LogTemp, Log, TEXT("ATTACK CHECKER - Hit Actor : %s"), *HitResult.GetActor()->GetName());
		AMonster* Enemy = Cast<AMonster>(HitResult.GetActor());
		FDamageEvent DamageEvent;
		if (Enemy == nullptr)
			return;
		Enemy->TakeDamage(Damage, DamageEvent, Attacker->GetController(), Attacker); //Temp
		Enemy->PlaySoundWave(Enemy->GetAudioComponent(), Attacker->GetWeapon()->GetHitSound());
	}
}
void UAttackChecker::ApplyMonsterDamageToPlayer(float Damage, class AMonster* Attacker, TArray<FOverlapResult> HitActor, AttackType AType)
{

}

void UAttackChecker::ApplyMonsterDamageToPlayerSectorForm(float Damage, AMonster* Attacker, TArray<FOverlapResult> HitActor, AttackType AType, float Angle)
{	
	if (HitActor.IsEmpty())//이거 지워도 되나?
		return;
	for (const FOverlapResult& Result : HitActor)
	{
		if (IsTargetInSectorForm(Cast<AActor>(Attacker), Result.GetActor(), Angle))
		{
			UE_LOG(LogTemp, Warning, TEXT("Target In Range : Skill4 Sevarog"));
			auto Player = Cast<AMyPlayer>(Result.GetActor());
			if (Player == nullptr)
				return;
			FDamageEvent DamageEvent;
			Player->OnDamaged(10.f, DamageEvent, Attacker->GetController(), Cast<AActor>(Attacker), AType); //Temp
		}
	}
}
#pragma endregion