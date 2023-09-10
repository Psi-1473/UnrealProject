
#include "PlayerSkillComponent.h"
#include "../Player/PlayerSkill.h"
#include "../../DEFINE.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../State/CharacterState.h"
#include "../../State/StateMachine.h"
#include "../../Creatures/Player/MyPlayer.h"

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
}

void UPlayerSkillComponent::ExecuteSkill(int SkillKey)
{
	
	if (RegisteredSkills[SkillKey] == nullptr)
		return;

	auto Player = Cast<AMyPlayer>(GetOwner());

	RegisteredSkills[SkillKey]->Execute(Player, RegisteredSkills[SkillKey]->GetIsRangeAttack());
}

void UPlayerSkillComponent::CancleCast(int SkillKey)
{
	if (RegisteredSkills[SkillKey] == nullptr)
		return;

	auto Player = Cast<AMyPlayer>(GetOwner());
	RegisteredSkills[SkillKey]->CancleCast(Player);
}

void UPlayerSkillComponent::AddSkill(UPlayerSkill* Skill)
{
	Skill->SetOwnerPlayer(OwnerPlayer);
	Skills.Add(Skill);
	Skill->InitSkillValue(Cast<AMyPlayer>(OwnerPlayer));
}


