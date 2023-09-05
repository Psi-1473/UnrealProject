#include "SoundActor.h"
#include "Components/AudioComponent.h"

void ISoundActor::PlaySoundWave(UAudioComponent* AudioComp, USoundWave* Sound)
{
	if (AudioComp == nullptr)
		return;

	if (Sound == nullptr)
		return;

	AudioComp->SetSound(Sound);
	AudioComp->Play();
	//AudioComp->SetSound(nullptr);
}
