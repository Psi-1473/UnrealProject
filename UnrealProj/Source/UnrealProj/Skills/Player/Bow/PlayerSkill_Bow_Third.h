#pragma once

#include "CoreMinimal.h"
#include "../PlayerSkill.h"
#include "PlayerSkill_Bow_Third.generated.h"

UCLASS()
class UNREALPROJ_API UPlayerSkill_Bow_Third : public UPlayerSkill
{
	GENERATED_BODY()
	
public:
	UPlayerSkill_Bow_Third();
	virtual void Execute(AActor* OwnerActor, bool bRangeAttack) override;
	virtual void PlayParticle(AActor* OwnerActor) override;

	void ParticlePlay();
private:
	UPROPERTY()
	class UParticleSystem* PlayerParticle;
	UPROPERTY()
	class UParticleSystem* BowParticle;
	UPROPERTY()
	class UParticleSystem* AttackParticle;
	UPROPERTY()
	class UParticleSystemComponent* BowParticleComp;
	UPROPERTY()
	TSubclassOf<class AProjectile> Arrow;

	UPROPERTY()
	FTimerHandle EffectTimer;

	UPROPERTY()
	int32 EffectCnt = 0;
};
