// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Information.h"
#include "../../MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Items/Item.h"
#include "../../Items/Weapons/Weapon.h"
#include "Components/TextBlock.h"

void UWidget_Information::SetInfo(InformationType Type, AItem* Item)
{
	FString Name;
	FString Explain;
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);
	auto GInstance = MyPlayer->GetInstance();
	if (Type == INFO_USEITEM)
	{
		Name = GInstance->GetUseItemData(Item->GetId())->Name;
		Explain = GInstance->GetUseItemData(Item->GetId())->Explanation;
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
			break;
		case WEAPONTYPE::WEAPON_ARROW:
			Name = GInstance->GetBowData(Item->GetId())->Name;
			Explain = GInstance->GetBowData(Item->GetId())->Explanation;
			break;
		default:
			break;
		}
	}
	else if (Type == INFO_SKILL)
	{
		// 검스킬인지 활스킬인지 확인필요할듯
	}

	Text_Name->SetText(FText::FromString(*Name));
	Text_Sub->SetText(FText::FromString(*Explain));
}

void UWidget_Information::SetPosition(FVector2D Pos)
{
	SetPositionInViewport(Pos);

}
