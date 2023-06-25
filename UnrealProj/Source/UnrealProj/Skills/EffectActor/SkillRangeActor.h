// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillRangeActor.generated.h"

UCLASS()
class UNREALPROJ_API ASkillRangeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASkillRangeActor();

protected:
	virtual void BeginPlay() override;

public:	
	//static ASkillRangeActor* MakeCircleRange(float Radius);
	void MakeThisToCircle(float Radius);

public:
	class UStaticMeshComponent* GetMesh() { return Mesh; }

private:
	UPROPERTY()
	class UStaticMeshComponent* Mesh;
	UPROPERTY()
	class USceneComponent* Root;

};
