
#include "PlayerSkillComponent.h"
#include "../Skill.h"
#include "../../DEFINE.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../State/CharacterState.h"
#include "../../State/StateMachine.h"

UPlayerSkillComponent::UPlayerSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	Skills.Init(nullptr, KEY_END);
}


void UPlayerSkillComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerSkillComponent::RegisterSkill(int SkillKey, USkill* Skill)
{
	Skills[SkillKey] = Skill;
}

void UPlayerSkillComponent::ExecuteSkill(int SkillKey)
{
	
	if (Skills[SkillKey] == nullptr)
		return;

	auto Player = Cast<AMyPlayer>(GetOwner());
	Player->SetState(STATE::SKILL);
	Skills[SkillKey]->Execute(Player);
}


