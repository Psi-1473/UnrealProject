#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageText.generated.h"

UCLASS()
class UNREALPROJ_API ADamageText : public AActor
{
	GENERATED_BODY()
	
public:	
	ADamageText();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	void Init();
private:
	

private:
	UPROPERTY(EditAnywhere)
	class UTextRenderComponent* TextRender;

	UPROPERTY()
	FTimerHandle DestroyTimerHandle;

};
