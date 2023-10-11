// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "SoundManager.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API USoundManager : public UObject
{
	GENERATED_BODY()
	
public:
	USoundManager();

	void Init(class UWorld* World);
	void SetBGM(class USoundBase* Sound);
	void SetBGM(FString SoundName);
	void SetArea(class AAreaBox* NewArea);
	void PlayAreaBgm();
	static void PlaySound(class UWorld* World, class USoundBase* Sound);



private:
	UPROPERTY()
	class AAmbientSound* BgmActor;

	UPROPERTY()
	class AAreaBox* Area;
};
