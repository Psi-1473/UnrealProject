#include "CameraEffectComponent.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../Creatures/Player/MyPlayerController.h"
#include "HitCameraShake.h"
#include "SkillHitCameraShake.h"


UCameraEffectComponent::UCameraEffectComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UCameraEffectComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}

void UCameraEffectComponent::ShakeCameraByEnum(CameraShakeType Type)
{
	auto Controller = OwnerPlayer->GetController<AMyPlayerController>();

	if (Type == SHAKE_BASIC)
	{
		Controller->ClientPlayCameraShake(UHitCameraShake::StaticClass(),
			1.f, ECameraAnimPlaySpace::CameraLocal);
	}
	if (Type == SHAKE_SKILL)
	{
		Controller->ClientPlayCameraShake(USkillHitCameraShake::StaticClass(),
			1.f, ECameraAnimPlaySpace::CameraLocal);
	}
}

void UCameraEffectComponent::ShakeCameraByClass(TSubclassOf<class ULegacyCameraShake> Type)
{
	auto Controller = OwnerPlayer->GetController<AMyPlayerController>();

	Controller->ClientPlayCameraShake(Type, 1.f, ECameraAnimPlaySpace::CameraLocal);
}


