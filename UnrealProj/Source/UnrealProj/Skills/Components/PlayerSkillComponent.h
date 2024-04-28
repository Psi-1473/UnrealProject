// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerSkillComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSkillPointChanged);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJ_API UPlayerSkillComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class USaveLoadManager;
public:	
	UPlayerSkillComponent();

protected:
	virtual void BeginPlay() override;

public:	
	void SetOwnerPlayer(TWeakObjectPtr<class AMyPlayer> Player) { OwnerPlayer = Player;}

	void RegisterSkill(int SkillKey, class UPlayerSkill* Skill);
	void ExecuteSkill(int SkillKey);
	void CancleCast(int SkillKey);
	void Update(float DeltaSeconds);

	void SkillsInit();
	void SwordSkillsInit();
	void BowSkillsInit();
	void DecreaseSkillPoint();
	void GainSkillPoint(int Value = 3);

	class UPlayerSkill* GetSwordSkill(int Idx) { return SwordSkills[Idx]; }
	class UPlayerSkill* GetBowSkill(int Idx) {return BowSkills[Idx]; };

	int32 GetSkillPoint() {return SkillPoint;}

private:
	UPROPERTY()
	TArray<class UPlayerSkill*> SwordSkills;

	UPROPERTY()
	TArray<class UPlayerSkill*> BowSkills;

	UPROPERTY()
	TArray<class UPlayerSkill*> RegisteredSkills;

	UPROPERTY()
	int32 SkillPoint = 3;

	UPROPERTY()
	TWeakObjectPtr<class AMyPlayer> OwnerPlayer;

public:
	FOnSkillPointChanged OnSkillPointChanged;
};
