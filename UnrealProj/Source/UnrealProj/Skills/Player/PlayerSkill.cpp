// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Animations/Player/PlayerAnim.h"
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

void UPlayerSkill::InitSkillValue(AMyPlayer* Player)
{
	FString ClassName = this->GetClass()->GetName();
	FString SkipString = TEXT("UPlayerSkill_");
	int32 StartPos = SkipString.Len() - 1;
	int32 EndPos = ClassName.Find(TEXT("_"), ESearchCase::IgnoreCase, ESearchDir::FromStart, StartPos);
	int32 Cnt = EndPos - StartPos;
	int32 IdCnt = ClassName.Len() - EndPos - 1;
	
	FString WTypeStr = ClassName.Mid(StartPos, Cnt);
	FString NumberStr = ClassName.Mid(EndPos + 1, IdCnt);

	int32 IdFromName = GetIdByName(NumberStr);

	auto GInstance = Player->GetInstance();
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, WTypeStr);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, NumberStr);

	SetWeaponType(WTypeStr);
	Id = GInstance->GetPlayerSkillDate(WTypeStr, IdFromName)->Id;
	CoolDown = GInstance->GetPlayerSkillDate(WTypeStr, IdFromName)->CoolDown;
	Name = GInstance->GetPlayerSkillDate(WTypeStr, IdFromName)->Name;
	Explanation = GInstance->GetPlayerSkillDate(WTypeStr, IdFromName)->Explanation;

}


int32 UPlayerSkill::GetIdByName(FString Str)
{
	int32 ReturnId = 0;

	if (Str == TEXT("First")) ReturnId = 1;
	if (Str == TEXT("Second")) ReturnId = 2;
	if (Str == TEXT("Third")) ReturnId = 3;

	return ReturnId;
}

void UPlayerSkill::SetWeaponType(FString Str)
{
	if(Str == TEXT("Sword"))
		WeaponType = WEAPONTYPE::WEAPON_SWORD;

	if (Str == TEXT("Bow"))
		WeaponType = WEAPONTYPE::WEAPON_ARROW;
}
