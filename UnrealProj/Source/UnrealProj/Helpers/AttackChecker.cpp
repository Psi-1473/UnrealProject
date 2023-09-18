// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackChecker.h"
#include "Kismet/GameplayStatics.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../Creatures/Monster/Monster.h"
#include "Engine/DamageEvents.h"
#include "Components/AudioComponent.h"
#include "../Items/Weapons/Weapon.h"

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

#pragma endregion

#pragma region Draw Functions
void UAttackChecker::DrawCubeHitBox(FVector StartVector, FVector EndVector, AActor* Attacker)
{
	//FVector Vec = Attacker->GetActorForwardVector() * Start;
	//FVector Center = StartVector + (EndVector - StartVector) / 2;
	//FQuat Rotation = FRotationMatrix::MakeFromZ(Vec).ToQuat();
	//FColor DrawColor;
	//if (bResult)
	//	DrawColor = FColor::Green;
	//else
	//	DrawColor = FColor::Red;

	//DrawDebugBox(GetWorld(), Center, FVector(SideRange, UpRange, FrontRange), Rotation, DrawColor, false, 2.f);

}

#pragma endregion

#pragma region Apply Damage Functions
void UAttackChecker::ApplyDamageToActor(AActor* Attacker, FHitResult HitActor)
{
	auto Player = Cast<AMyPlayer>(Attacker);

	if (Player)
		ApplyPlayerDamageToMonster(Player, HitActor);
}

void UAttackChecker::ApplyDamageToActors(AActor* Attacker, TArray<FHitResult> HitActors)
{
	auto Player = Cast<AMyPlayer>(Attacker);

	if (Player)
		ApplyPlayerDamageToMonster(Player, HitActors);
}

void UAttackChecker::ApplyPlayerDamageToMonster(AMyPlayer* Attacker, FHitResult HitActor)
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

void UAttackChecker::ApplyPlayerDamageToMonster(AMyPlayer* Attacker, TArray<FHitResult> HitActors)
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
		Enemy->TakeDamage(10.f, DamageEvent, Attacker->GetController(), Attacker); //Temp
		Enemy->PlaySoundWave(Enemy->GetAudioComponent(), Attacker->GetWeapon()->GetHitSound());
	}
}
#pragma endregion