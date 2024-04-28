
#include "PlayerSkillComponent.h"
#include "../Player/PlayerSkill.h"
#include "../../DEFINE.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../State/CharacterState.h"
#include "../../State/StateMachine.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Skills/Player/PlayerSkill.h"
#include "../../Skills/Skill.h"
#include "../../Stat/PlayerStatComponent.h"
#include "../../Items/Weapons/Weapon.h"
#include "../../Inventory/EquipItemComponent.h"

#pragma region Skill Headers
#include "../../Skills/Player/Sword/PlayerSkill_Sword_First.h"
#include "../../Skills/Player/Sword/PlayerSkill_Sword_Second.h"
#include "../../Skills/Player/Sword/PlayerSkill_Sword_Third.h"
#include "../../Skills/Player/Bow/PlayerSkill_Bow_First.h"
#include "../../Skills/Player/Bow/PlayerSkill_Bow_Second.h"
#include "../../Skills/Player/Bow/PlayerSkill_Bow_Third.h"
#pragma endregion 
UPlayerSkillComponent::UPlayerSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	RegisteredSkills.Init(nullptr, KEY_END);
}


void UPlayerSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UPlayerSkillComponent::RegisterSkill(int SkillKey, UPlayerSkill* Skill)
{
	RegisteredSkills[SkillKey] = Skill;
	Skill->SetRegisteredKey(SkillKey);
}

void UPlayerSkillComponent::ExecuteSkill(int SkillKey)
{
	
	if (RegisteredSkills[SkillKey] == nullptr) return;
	if (RegisteredSkills[SkillKey]->GetRemainingTime() > 0.f) return;

	auto Player = Cast<AMyPlayer>(GetOwner());
	if (RegisteredSkills[SkillKey]->GetWeaponType() != Player->GetEquipComponent()->GetWeapon()->GetType()) return;
	
	int RequiredMp = RegisteredSkills[SkillKey]->GetMp();
	if (Player->GetStatComponent()->GetMp() < RequiredMp) return;

	Player->GetStatComponent()->SetMp(Player->GetStatComponent()->GetMp() - RequiredMp);
	RegisteredSkills[SkillKey]->Execute(Player, RegisteredSkills[SkillKey]->GetIsRangeAttack());
}

void UPlayerSkillComponent::CancleCast(int SkillKey)
{
	if (RegisteredSkills[SkillKey] == nullptr)
		return;

	auto Player = Cast<AMyPlayer>(GetOwner());
	RegisteredSkills[SkillKey]->CancleCast(Player);
}

void UPlayerSkillComponent::Update(float DeltaSeconds)
{
	for (int i = 0; i < SwordSkills.Num(); i++)
	{
		if(SwordSkills[i] == nullptr)
			continue;
		SwordSkills[i]->DecreaseCoolDown(DeltaSeconds);
	}

	for (int i = 0; i < BowSkills.Num(); i++)
	{
		if (BowSkills[i] == nullptr)
			continue;
		BowSkills[i]->DecreaseCoolDown(DeltaSeconds);
	}
}

void UPlayerSkillComponent::SkillsInit()
{
	SwordSkillsInit();
	BowSkillsInit();
}

void UPlayerSkillComponent::SwordSkillsInit()
{
	//	TEMP : Skill Sword
	SwordSkills.Add(nullptr);
	UPlayerSkill_Sword_First* Sword1 = NewObject<UPlayerSkill_Sword_First>();
	UPlayerSkill_Sword_Second* Sword2 = NewObject<UPlayerSkill_Sword_Second>();
	UPlayerSkill_Sword_Third* Sword3 = NewObject<UPlayerSkill_Sword_Third>();

	Sword1->InitSkillValue(Cast<AMyPlayer>(OwnerPlayer));
	Sword2->InitSkillValue(Cast<AMyPlayer>(OwnerPlayer));
	Sword3->InitSkillValue(Cast<AMyPlayer>(OwnerPlayer));

	SwordSkills.Add(Sword1);
	SwordSkills.Add(Sword2);
	SwordSkills.Add(Sword3);
}

void UPlayerSkillComponent::BowSkillsInit()
{
	BowSkills.Add(nullptr);
	UPlayerSkill_Bow_First* Bow1 = NewObject<UPlayerSkill_Bow_First>();
	UPlayerSkill_Bow_Second* Bow2 = NewObject<UPlayerSkill_Bow_Second>();
	UPlayerSkill_Bow_Third* Bow3 = NewObject<UPlayerSkill_Bow_Third>();

	Bow1->InitSkillValue(Cast<AMyPlayer>(OwnerPlayer));
	Bow2->InitSkillValue(Cast<AMyPlayer>(OwnerPlayer));
	Bow3->InitSkillValue(Cast<AMyPlayer>(OwnerPlayer));

	BowSkills.Add(Bow1);
	BowSkills.Add(Bow2);
	BowSkills.Add(Bow3);
}

void UPlayerSkillComponent::DecreaseSkillPoint()
{
	SkillPoint--;
	OnSkillPointChanged.Broadcast();
}

void UPlayerSkillComponent::GainSkillPoint(int Value)
{
	SkillPoint += Value;
	OnSkillPointChanged.Broadcast();
}


