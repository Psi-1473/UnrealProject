// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Animations/Player/PlayerAnim.h"
#include "../Components/PlayerSkillComponent.h"
#include "../EffectActor//SkillRangeActor.h"
#include "../../Items/Weapons/Weapon.h"
#include "../../MyGameInstance.h"

void UPlayerSkill::SetDefaultValue()
{
	OwnerPlayer->SetState(STATE::SKILL);
	OwnerPlayer->SetSkill(this);
	OwnerPlayer->GetAnimInst()->PlaySkillMontage(Id);
}



void UPlayerSkill::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	Super::Execute(OwnerActor, bRangeAttack);
	OwnerPlayer = Cast<AMyPlayer>(OwnerActor);

	UE_LOG(LogTemp, Warning, TEXT("Cooldown %f : %d"), RemainingTime, CoolDown);
	if (RemainingTime > 0)
		return;

	if (OwnerPlayer == nullptr)
		return;

	if (WeaponType != OwnerPlayer->GetWeapon()->GetType())
		return;

	if (!bRangeAttack)
		OwnerPlayer->SetState(STATE::SKILLCAST);
}

void UPlayerSkill::CancleCast(AActor* OwnerActor)
{
	OwnerPlayer = Cast<AMyPlayer>(OwnerActor);
	OwnerPlayer->GetAnimInst()->SetBowCast(false);
	OwnerPlayer->SetState(STATE::IDLE);
	if (OwnerPlayer->GetSpawnedRangeActor())
	{
		OwnerPlayer->GetSpawnedRangeActor()->Destroy();
		OwnerPlayer->SetRangeActor(nullptr);
	}
}

void UPlayerSkill::SkillEnd()
{
	Super::SkillEnd();
}

void UPlayerSkill::InitSkillValue(AMyPlayer* Player)
{
	OwnerPlayer = Player;
	FString ClassName = this->GetClass()->GetName();
	FString SkipString = TEXT("UPlayerSkill_");
	int32 StartPos = SkipString.Len() - 1;
	int32 EndPos = ClassName.Find(TEXT("_"), ESearchCase::IgnoreCase, ESearchDir::FromStart, StartPos);
	int32 Cnt = EndPos - StartPos;
	int32 IdCnt = ClassName.Len() - EndPos - 1;
	
	FString WTypeStr = ClassName.Mid(StartPos, Cnt);
	FString NumberStr = ClassName.Mid(EndPos + 1, IdCnt);
	int32 IdFromName = GetIdByName(NumberStr);

	auto GInstance = Player->GetInstance(); // 여기가 문제
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, WTypeStr);
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, NumberStr);

	SetWeaponType(WTypeStr);
	Id = GInstance->GetPlayerSkillData(WTypeStr, IdFromName)->Id;
	CoolDown = GInstance->GetPlayerSkillData(WTypeStr, IdFromName)->CoolDown;
	Name = GInstance->GetPlayerSkillData(WTypeStr, IdFromName)->Name;
	Explanation = GInstance->GetPlayerSkillData(WTypeStr, IdFromName)->Explanation;
	Mp = GInstance->GetPlayerSkillData(WTypeStr, IdFromName)->Mp;

	UE_LOG(LogTemp, Warning, TEXT("Cooldown Load %d "), CoolDown);
}
void UPlayerSkill::LevelUp()
{
	SkillLevel++;
	OwnerPlayer->GetSkillComponent()->DecreaseSkillPoint();
	// 레벨에 맞게 능력치 변경
}
void UPlayerSkill::DecreaseCoolDown(float DeltaSeconds)
{
	if (RemainingTime < 0.f) RemainingTime = 0.f;
	if (RemainingTime == 0.f) return;

	RemainingTime -= DeltaSeconds;
}

int32 UPlayerSkill::GetIdByName(FString Str)
{
	int32 ReturnId = 0;

	if (Str == TEXT("First")) ReturnId = 1;
	if (Str == TEXT("Second")) ReturnId = 2;
	if (Str == TEXT("Third")) ReturnId = 3;
	if (Str == TEXT("Fourth")) ReturnId = 4;

	return ReturnId;
}

void UPlayerSkill::SetWeaponType(FString Str)
{
	if(Str == TEXT("Sword"))
		WeaponType = WEAPONTYPE::WEAPON_SWORD;

	if (Str == TEXT("Bow"))
		WeaponType = WEAPONTYPE::WEAPON_ARROW;
}