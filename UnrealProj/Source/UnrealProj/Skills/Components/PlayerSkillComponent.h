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
	void SetOwnerPlayer(TWeakObjectPtr<class AMyPlayer> Player) { OwnerPlayer = Player; }
	void RegisterSkill(int SkillKey, class UPlayerSkill* Skill);
	void ExecuteSkill(int SkillKey);
	void CancleCast(int SkillKey);
	void AddSkill(class UPlayerSkill* Skill);
	void Update(float DeltaSeconds);

	int GetSkillNumber() { return Skills.Num(); }
	TArray<class UPlayerSkill*>& GetSkills() { return Skills; }
private:
	UPROPERTY()
	TArray<class UPlayerSkill*> Skills;

	UPROPERTY()
	TArray<class UPlayerSkill*> RegisteredSkills;

	UPROPERTY()
	TWeakObjectPtr<class AMyPlayer> OwnerPlayer;
};
