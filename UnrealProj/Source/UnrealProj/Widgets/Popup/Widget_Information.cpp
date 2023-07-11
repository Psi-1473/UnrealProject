// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Information.h"
#include "../../MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Items/Item.h"
#include "../../Items/Weapons/Weapon.h"
#include "Components/TextBlock.h"
#include "../../Skills/Skill.h"

void UWidget_Information::SetInfoByItem(InformationType Type, AItem* Item)
{
	FString Name;
	FString Explain;
	FString Value;
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);
	auto GInstance = MyPlayer->GetInstance();
	if (Type == INFO_USEITEM)
	{
		Name = GInstance->GetUseItemData(Item->GetId())->Name;
		Explain = GInstance->GetUseItemData(Item->GetId())->Explanation;
		Value = TEXT("");
	}
	else if (Type == INFO_WEAPON)
	{
		auto Weapon = Cast<AWeapon>(Item);
		WEAPONTYPE WType = Weapon->GetType();

		switch (WType)
		{
		case WEAPONTYPE::WEAPON_SWORD:
			Name = GInstance->GetSwordData(Item->GetId())->Name;
			Explain = GInstance->GetSwordData(Item->GetId())->Explanation;
			Value = FString::FromInt(GInstance->GetSwordData(Item->GetId())->Damage);
			break;
		case WEAPONTYPE::WEAPON_ARROW:
			Name = GInstance->GetBowData(Item->GetId())->Name;
			Explain = GInstance->GetBowData(Item->GetId())->Explanation;
			Value = FString::FromInt(GInstance->GetBowData(Item->GetId())->Damage);
			break;
		default:
			break;
		}
	}


	Text_Name->SetText(FText::FromString(*Name));
	Text_Sub->SetText(FText::FromString(*Explain));
	Text_Value->SetText(FText::FromString(*Value));
}

void UWidget_Information::SetInfoBySkill(USkill* Skill)
{
	FString Name;
	FString Explain;
	FString Value;
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);
	auto GInstance = MyPlayer->GetInstance();
	Name = Skill->GetSkillInfo()->Name;
	Explain = Skill->GetSkillInfo()->Explanation;

	Text_Name->SetText(FText::FromString(*Name));
	Text_Sub->SetText(FText::FromString(*Explain));
}

void UWidget_Information::SetPosition(FVector2D Pos)
{
	SetPositionInViewport(Pos);

}
