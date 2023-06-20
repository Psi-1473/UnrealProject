// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillEffectActor.generated.h"

UCLASS()
class UNREALPROJ_API ASkillEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASkillEffectActor();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* ParticleComponent;

	UPROPERTY(EditAnywhere)
	class USceneComponent* RootScene;
};
