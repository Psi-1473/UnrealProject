#include "EquipItemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../State/StateMachine.h"
#include "../Items/Weapons/Weapon.h"

UEquipItemComponent::UEquipItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UEquipItemComponent::EquipWeapon(AWeapon* _Weapon)
{
	EquipedWeapon = _Weapon;
	OwnerPlayer->GetStateMachine()->SetWeaponState(_Weapon->GetType());

	ChangeWeaponMesh();
}

void UEquipItemComponent::ChangeWeaponMesh()
{
	if (EquipedWeapon->GetIsRight())
	{
		OwnerPlayer->GetLeftWeaponMesh()->SetStaticMesh(nullptr);
		OwnerPlayer->GetRightWeaponMesh()->SetStaticMesh(EquipedWeapon->GetStaticMesh());
	}
	else
	{
		OwnerPlayer->GetRightWeaponMesh()->SetStaticMesh(nullptr);
		OwnerPlayer->GetLeftWeaponMesh()->SetStaticMesh(EquipedWeapon->GetStaticMesh());
	}

	OwnerPlayer->SetAnimByWeapon(EquipedWeapon->GetType());
}

void UEquipItemComponent::BeginPlay()
{
	Super::BeginPlay();

	
}




