#include "VehicleComponent.h"
#include "../Creatures/Vehicles/Vehicle.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../State/StateMachine.h"
#include "../Animations/Player/PlayerAnim.h"

UVehicleComponent::UVehicleComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UVehicleComponent::SetOwnerPlayer(TWeakObjectPtr<AMyPlayer> Player)
{
	OwnerPlayer = Player;
}

void UVehicleComponent::AddNewVehicle(AVehicle* NewVehicle)
{
	if(Vehicles.Find(NewVehicle) == false)
		Vehicles.Add(NewVehicle);
}

void UVehicleComponent::RemoveVehicle(AVehicle* OldVehicle)
{
	Vehicles.Remove(OldVehicle);
}

void UVehicleComponent::RegisterVehicle(AVehicle* Vehicle)
{
	VehicleInUse = Vehicle;
}

void UVehicleComponent::RideVehicle()
{
	if(VehicleInUse == false) 
	{
		UE_LOG(LogTemp, Warning, TEXT("RegisteredVehicle null"));
		return;
	}

	if(IsRiding) 
	{
		UE_LOG(LogTemp, Warning, TEXT("You're already riding"));
		return;
	}

	IsRiding = true;
	// 1. Ż �� ����
	VehicleInUse->Spawn();
	// 2. �÷��̾ Ż �� Ÿ�� �ִϸ��̼� ����
	OwnerPlayer->GetStateMachine()->SetState(STATE::RIDE);
	//OwnerPlayer->GetAnimInst()->PlayRideAnim();
	// �ִϸ��̼� ����, �ִϸ��̼� ���� ���� �ٲٴ� �Լ� ���
	// 3. ���� ��ġ�� �÷��̾� ��ġ �� ����

	// 4. �÷��̾� ���� -> ���̵����� ����
	// ���̵� ���¿��� �� ��
	// 1) ���̵��� �°� ���� ī�޶� ����
	// 2) �����̸� ���� �����̰� �ϰ� �÷��̾�� Vehicle�� ���󰡰Ը� �ϱ�
	
}

void UVehicleComponent::Dismount()
{
	
}


