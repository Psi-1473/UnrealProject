#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SoundActor.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USoundActor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALPROJ_API ISoundActor
{
	GENERATED_BODY()

public:
	void PlaySoundWave(class UAudioComponent* AudioComp, class USoundWave* Sound);
};
