// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponState.h"
#include "StateMachine.h"
#include "CharacterState.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../Creatures/Monster/Monster.h"
#include "../Skills/Player/PlayerSkill.h"
#include "../Animations/Player/PlayerAnim.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "../Projectiles/Projectile.h"
#include "../Projectiles/Player/Arrow.h"
#include "../Items/Weapons/Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "../Helpers/AttackChecker.h"

void UWeaponState::OnLeftMouseClicked(AMyPlayer* Player)
{
	if (Machine->GetState() != Machine->GetState(STATE::IDLE) &&
		Machine->GetState() != Machine->GetState(STATE::MOVE) &&
		Machine->GetState() != Machine->GetState(STATE::JUMP) &&
		Machine->GetState() != Machine->GetState(STATE::ATTACK) &&
		Machine->GetState() != Machine->GetState(STATE::SKILLCAST))
		return;

	if (Machine->GetState() == Machine->GetState(STATE::SKILL))
		return;

	if (Machine->GetState() == Machine->GetState(STATE::SKILLCAST))
		Player->GetSkill()->CastToExecute(Player);
	else
	{
		if (Machine->GetState()->GetState() != STATE::ATTACK)
			Machine->SetState(STATE::ATTACK);

		Player->GetAnimInst()->PlayAttackMontage();
	}
}


#pragma region SwordState
void USwordState::OnLeftMouseClicked(AMyPlayer* Player)
{
	UWeaponState::OnLeftMouseClicked(Player);
}

void USwordState::OnRightMouseClicked(AMyPlayer* Player)
{
}

void USwordState::OnRightMouseReleased(AMyPlayer* Player)
{
}

void USwordState::OnUpdate()
{
}

#pragma endregion


#pragma region BowState
void UBowState::OnLeftMouseClicked(AMyPlayer* Player)
{
	UWeaponState::OnLeftMouseClicked(Player);
}

void UBowState::OnRightMouseClicked(AMyPlayer* Player)
{
	if (Machine->GetState() == Machine->GetState(STATE::ATTACK) && CameraMoved == false)
		return;

	ZoomIn(Player);
}

void UBowState::OnRightMouseReleased(AMyPlayer* Player)
{
	if (Machine->GetState() == Machine->GetState(STATE::ATTACK) && CameraMoved == false)
		return;
	ZoomOut(Player);
}

void UBowState::OnUpdate()
{
	FindTarget();
}


void UBowState::ZoomIn(AMyPlayer* Player)
{
	if (Machine->GetState() != Machine->GetState(STATE::IDLE) &&
		Machine->GetState() != Machine->GetState(STATE::MOVE) &&
		Machine->GetState() != Machine->GetState(STATE::JUMP))
		return;
	auto Movement = Cast<UCharacterMovementComponent>(Player->GetMovementComponent());
	Player->GetCamera()->SetRelativeLocation(Player->GetCamera()->GetRelativeLocation() + FVector(0.f, 60.f, 0.f));
	Player->GetCamera()->FieldOfView = 75.f;
	Movement->MaxWalkSpeed = 350.f;
	CameraMoved = true;
	bZoom = true;
}

void UBowState::ZoomOut(AMyPlayer* Player)
{
	if (CameraMoved == false) return;
	auto Movement = Cast<UCharacterMovementComponent>(Player->GetMovementComponent());
	Player->GetCamera()->SetRelativeLocation(Player->GetCamera()->GetRelativeLocation() + FVector(0.f, -60.f, 0.f));
	Player->GetCamera()->FieldOfView = 90.f;
	Movement->MaxWalkSpeed = 600.f;
	CameraMoved = false;
	bZoom = false;
}
void UBowState::FindTarget()
{
	TArray<FOverlapResult> OutOverlaps = UAttackChecker::PlayerCircleCheck(Machine->GetOwner()->GetActorLocation(),
	1250.f,
	200.f,
	ECollisionChannel::ECC_GameTraceChannel5,
	Machine->GetOwner());

	AActor* TempTarget = nullptr;

	for (int i = 0; i < OutOverlaps.Num(); i++)
	{
		if (UAttackChecker::IsTargetInSectorForm(Machine->GetOwner(), OutOverlaps[i].GetActor(), 80.f))
		{
			if(Cast<AMyPlayer>(OutOverlaps[i].GetActor()))
				continue;

			if(TempTarget == nullptr || TempTarget->GetDistanceTo(Machine->GetOwner()) > OutOverlaps[i].GetActor()->GetDistanceTo(Machine->GetOwner()))
				TempTarget = OutOverlaps[i].GetActor();
		}
	}
	if(Cast<AMonster>(Target))
		Cast<AMonster>(Target)->SetTargetUI(false);
	Target = TempTarget;
	if (Cast<AMonster>(Target))
		Cast<AMonster>(Target)->SetTargetUI(true);
}
void UBowState::Fire()
{
	FVector ArrowDir = GetViewportToWorld(Cast<APlayerController>(Machine->GetOwner()->GetController()));
	FireArrow(ArrowDir);
}
void UBowState::FireArrow(FVector DestPos)
{
	AMyPlayer* Player = Machine->GetOwner();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Player;
	SpawnParams.Instigator = Player->GetInstigator();

	FVector CameraLocation;
	FRotator CameraRotation;
	Player->GetActorEyesViewPoint(CameraLocation, CameraRotation);
	//CameraRotation.Pitch += 5.f;
	AProjectile* Projectile = Player->GetWorld()->SpawnActor<AArrow>(Player->GetWeapon()->GetArrow(),
		Player->GetActorLocation() + Player->GetActorRightVector() * 15.f + Player->GetActorUpVector() * 65.f,
		CameraRotation,
		SpawnParams);
	FVector ArrowVector;
	if (bArrowTarget)
		ArrowVector = DestPos - Projectile->GetActorLocation();
	else
		ArrowVector = DestPos;
	ArrowVector.Normalize();
	if (Projectile)
	{
		if (bZoom)
			Projectile->SetAttackStrength(true);
		else
			Projectile->SetAttackStrength(false);
		Projectile->FireInDirection(ArrowVector, 2.f);
	}
}
FVector UBowState::GetViewportToWorld(APlayerController* Controller)
{
	int ViewportX, ViewportY;
	FVector WorldPos;
	FVector WorldDir;

	Controller->GetViewportSize(ViewportX, ViewportY);
	ViewportX = ViewportX / 2;
	ViewportY = ViewportY / 2;
	ViewportY -= 40;
	Controller->DeprojectScreenPositionToWorld((float)ViewportX, (float)ViewportY, WorldPos, WorldDir);
	UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), WorldPos.X, WorldPos.Y, WorldPos.Z);
	UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), WorldDir.X, WorldDir.Y, WorldDir.Z);

	FVector ResultDir = GetArrowDir(WorldPos, WorldDir);
	return ResultDir;
}
FVector UBowState::GetArrowDir(FVector Start, FVector Dir)
{
	if(Target != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target On : %s"), *Target->GetActorNameOrLabel());
		bArrowTarget = true;
		return Target->GetActorLocation();
	}
	FVector EndPos = Start + (Dir * 5000.f);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes; // 히트 가능한 오브젝트 유형들.
	TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
	TEnumAsByte<EObjectTypeQuery> WorldDynamic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic);
	TEnumAsByte<EObjectTypeQuery> MonsterCol = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	TEnumAsByte<EObjectTypeQuery> PawnCol = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
	ObjectTypes.Add(WorldStatic);
	ObjectTypes.Add(WorldDynamic);
	ObjectTypes.Add(MonsterCol);
	ObjectTypes.Add(PawnCol);

	TArray<AActor*> IgnoreActors; // 무시할 액터들.

	FHitResult HitResult; // 히트 결과 값 받을 변수.

	bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(
		Machine->GetOwner()->GetWorld(),
		Start,
		EndPos,
		ObjectTypes,
		false,
		IgnoreActors, // 무시할 것이 없다고해도 null을 넣을 수 없다.
		EDrawDebugTrace::ForDuration,
		HitResult,
		true
		// 여기 밑에 3개는 기본 값으로 제공됨. 바꾸려면 적으면 됨.
		, FLinearColor::Transparent
		, FLinearColor::Transparent
		, 0.0f
	);

	FVector DestinationPos;
	if (Result == true)
	{
		DestinationPos = HitResult.Location;
		bArrowTarget = true;
		UE_LOG(LogTemp, Warning, TEXT("Arrow Hit O"));
	}
	else
	{
		DestinationPos = Dir;
		bArrowTarget = false;
		UE_LOG(LogTemp, Warning, TEXT("Arrow Hit X"));
	}
	return DestinationPos;
}
#pragma endregion


