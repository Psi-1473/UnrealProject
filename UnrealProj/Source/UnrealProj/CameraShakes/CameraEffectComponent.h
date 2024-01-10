#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../DEFINE.h"
#include "CameraEffectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJ_API UCameraEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCameraEffectComponent();

protected:
	virtual void BeginPlay() override;

public:
	void ShakeCameraByEnum(CameraShakeType Type);
	void ShakeCameraByClass(TSubclassOf<class ULegacyCameraShake> Type);

	void SetOwnerPlayer(TWeakObjectPtr<class AMyPlayer> Player) { OwnerPlayer = Player; }
private:
	TWeakObjectPtr<class AMyPlayer> OwnerPlayer;
};
