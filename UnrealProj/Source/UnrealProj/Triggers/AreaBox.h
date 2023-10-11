// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AreaBox.generated.h"

UCLASS()
class UNREALPROJ_API AAreaBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAreaBox();

protected:
	virtual void BeginPlay() override;
public:

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FString GetAreaTypeName() { return AreaTypeName; }
	FString GetAreaName() { return AreaName; }
private:
	void SetAreaTypeName();
	UUserWidget* ShowAreaUI();


private:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY()
	FString AreaTypeName;

	UPROPERTY(EditAnywhere)
	FString AreaName;
};
