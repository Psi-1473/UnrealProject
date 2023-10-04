// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerSkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJ_API UPlayerSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerSkillComponent();

protected:
	virtual void BeginPlay() override;

public:	
	void SetOwnerPlayer(TWeakObjectPtr<class AMyPlayer> Player) { OwnerPlayer = Player; SwordSkillsInit(); }
	void RegisterSkill(int SkillKey, class UPlayerSkill* Skill);
	void ExecuteSkill(int SkillKey);
	void CancleCast(int SkillKey);
	void Update(float DeltaSeconds);

	void SwordSkillsInit();
	void BowSkillsInit();

	class UPlayerSkill* GetSwordSkill(int Idx) { return SwordSkills[Idx]; }
	class UPlayerSkill* GetBowSkill(int Idx) {return BowSkills[Idx]; };

private:
	UPROPERTY()
	TArray<class UPlayerSkill*> SwordSkills;

	UPROPERTY()
	TArray<class UPlayerSkill*> BowSkills;

	UPROPERTY()
	TArray<class UPlayerSkill*> RegisteredSkills;

	UPROPERTY()
	TWeakObjectPtr<class AMyPlayer> OwnerPlayer;
};
