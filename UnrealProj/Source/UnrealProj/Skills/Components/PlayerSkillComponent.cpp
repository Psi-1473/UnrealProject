
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

	if (RegisteredSkills[SkillKey]->GetRemainingTime() > 0.f)
		return;

	auto Player = Cast<AMyPlayer>(GetOwner());
	if (RegisteredSkills[SkillKey]->GetWeaponType() != Player->GetWeapon()->GetType())
		return;
	
	int RequiredMp = RegisteredSkills[SkillKey]->GetMp();


	if (Player->GetStatComponent()->GetMp() < RequiredMp)
		return;

	Player->GetStatComponent()->SetMp(Player->GetStatComponent()->GetMp() - RequiredMp);
	UE_LOG(LogTemp, Warning, TEXT("MP : %d"), Player->GetStatComponent()->GetMp());
	

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

void UPlayerSkillComponent::Update(float DeltaSeconds)
{
	for (int i = 0; i < Skills.Num(); i++)
	{
		Skills[i]->DecreaseCoolDown(DeltaSeconds);
	}
}


