// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipItemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJ_API UEquipItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquipItemComponent();

public:
	void SetInfo(TWeakObjectPtr<class AMyPlayer>  Player) { OwnerPlayer = Player; }

	void EquipWeapon(class AWeapon* _Weapon);
	void ChangeWeaponMesh();

protected:
	virtual void BeginPlay() override;



private:
	UPROPERTY()
	TWeakObjectPtr<class AMyPlayer> OwnerPlayer;
	
	UPROPERTY()
	class AWeapon* EquipedWeapon;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* LWeapon;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* RWeapon;
		
};
