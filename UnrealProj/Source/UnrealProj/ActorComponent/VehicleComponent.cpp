#include "VehicleComponent.h"
#include "../Creatures/Vehicles/Vehicle.h"
#include "../Creatures/Vehicles/VehicleInfo.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../State/StateMachine.h"
#include "../Animations/Player/PlayerAnim.h"
#include "../Managers/ResourceManager.h"
#include "../State/VehicleStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"

UVehicleComponent::UVehicleComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UVehicleComponent::SetOwnerPlayer(TWeakObjectPtr<AMyPlayer> Player)
{
	OwnerPlayer = Player;
}

void UVehicleComponent::AddNewVehicle(UVehicleInfo* NewVehicle)
{
	if(Vehicles.Find(NewVehicle) == false)
		Vehicles.Add(NewVehicle);
}

void UVehicleComponent::RemoveVehicle(UVehicleInfo* OldVehicle)
{
	Vehicles.Remove(OldVehicle);
}

void UVehicleComponent::RegisterVehicle(UVehicleInfo* Vehicle)
{
	RegisteredVehicle = Vehicle;
}

void UVehicleComponent::RideVehicle()
{
	if(RegisteredVehicle == nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("RegisteredVehicle null"));
		return;
	}

	if(IsRiding) 
	{
		UE_LOG(LogTemp, Warning, TEXT("You're already riding"));
		if (VehicleInUse != nullptr && VehicleInUse->GetStateMachine()->GetState()->StateEnum == VSTATE::IDLE)
		{
			UE_LOG(LogTemp, Warning, TEXT("Despawn Vehicle"));
			DespawnVehicle();
		}
		return;
	}
	if (OwnerPlayer->GetStateMachine()->GetState()->GetState() != STATE::IDLE)
		return;

	IsRiding = true;

	SpawnVehicle();
	OwnerPlayer->GetStateMachine()->SetState(STATE::RIDE);
}

void UVehicleComponent::SpawnVehicle()
{
	FString Dir = RegisteredVehicle->GetDir();

	auto SpawnClass = OwnerPlayer->GetInstance()->GetResourceMgr()->Instantiate<AVehicle>(
		Dir,
		Cast<AActor>(OwnerPlayer),
		OwnerPlayer->GetActorLocation(),
		OwnerPlayer->GetActorRotation()
	);

	if (OwnerPlayer != nullptr)
	{

		SpawnClass->AttachToActor(Cast<AActor>(OwnerPlayer), FAttachmentTransformRules::KeepWorldTransform);
		UE_LOG(LogTemp, Warning, TEXT("Attach to Player"));
	}
	
	SpawnClass->SetInfo(*RegisteredVehicle);
	SpawnClass->SetOwnerPlayer(OwnerPlayer);
	VehicleInUse = SpawnClass;
}

void UVehicleComponent::DespawnVehicle()
{
	if(VehicleInUse->GetStateMachine()->GetState()->StateEnum != VSTATE::IDLE)
		return;

	VehicleInUse->SetState(VSTATE::DISMOUNT);


}
void UVehicleComponent::StartDash()
{
	if(VehicleInUse == nullptr)
		return;
	auto MovementComponent = Cast<UCharacterMovementComponent>(OwnerPlayer->GetCharacterMovement());
	MovementComponent->MaxWalkSpeed = VehicleInUse->GetDashSpeed();
	VehicleInUse->SetIsDash(true);
}

void UVehicleComponent::EndDash()
{
	if (VehicleInUse == nullptr)
		return;
	auto MovementComponent = Cast<UCharacterMovementComponent>(OwnerPlayer->GetCharacterMovement());
	MovementComponent->MaxWalkSpeed = VehicleInUse->GetSpeed();
	VehicleInUse->SetIsDash(false);
}



