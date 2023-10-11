// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManager.h"
#include "Sound/SoundWave.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/AmbientSound.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"
#include "../MyGameInstance.h"
#include "../Triggers/AreaBox.h"

USoundManager::USoundManager()
{

}

void USoundManager::Init(UWorld* World)
{
	BgmActor = World->SpawnActor<AAmbientSound>(AAmbientSound::StaticClass(),
		FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));

	SetBGM(TEXT("Main"));
}

void USoundManager::SetBGM(USoundBase* Sound)
{
	BgmActor->GetAudioComponent()->SetSound(Sound);
	BgmActor->Play();
}

void USoundManager::SetBGM(FString SoundName)
{
	FString Directory = TEXT("/Script/Engine.SoundWave'/Game/10_Sound/BGM/BGM_");
	Directory += SoundName + TEXT(".BGM_") + SoundName + TEXT("'");
	class USoundWave* Sound;
	Sound = LoadObject<USoundWave>(NULL, *Directory, NULL, LOAD_None, NULL);

	if (Sound == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sound Null! %s"), *SoundName);
	}

	BgmActor->GetAudioComponent()->SetSound(Sound);
	BgmActor->Play();
}

void USoundManager::SetArea(AAreaBox* NewArea)
{
	if (NewArea == Area)
		return;

	Area = NewArea;

	// 만약 지역 상관없이 브금이 유지되어야 하는 특수상황이 아니라면
	SetBGM(Area->GetAreaTypeName());
}

void USoundManager::PlayAreaBgm()
{
	SetBGM(Area->GetAreaTypeName());
}

void USoundManager::PlaySound(UWorld* World, USoundBase* Sound)
{
	UGameplayStatics::PlaySound2D(World, Sound);
	
}
