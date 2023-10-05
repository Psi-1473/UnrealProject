#pragma once

#include "CoreMinimal.h"
#include "../PlayerSkill.h"
#include "PlayerSkill_Bow_Third.generated.h"

UCLASS()
class UNREALPROJ_API UPlayerSkill_Bow_Third : public UPlayerSkill
{
	GENERATED_BODY()
	
public:
	virtual void Execute(AActor* OwnerActor, bool bRangeAttack) override;
	virtual void PlayParticle(AActor* OwnerActor) override;

private:
	class UParticleSystem* PlayerParticle;
};
