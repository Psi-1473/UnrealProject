// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "SkillRangeActor.generated.h"

UCLASS()
class UNREALPROJ_API ASkillRangeActor : public ADecalActor
{
	GENERATED_BODY()
	
public:	
	ASkillRangeActor();

protected:
	virtual void BeginPlay() override;

public:	
	void MakeThisToCircle(float Radius);
	void SetRange(AActor* OwnerActor, bool bTemp, float Size, float Angle = 360.f);

	void MoveRangeActor(FVector Dir, FVector PlayerPos, float MaxDistance);
	void DestroyThis();
private:
	UPROPERTY()
	class UMaterial* Material;

	UPROPERTY()
	struct FTimerHandle DestroyTimer;
};
