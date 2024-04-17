// Fill out your copyright notice in the Description page of Project Settings.


#include "HorseAnimInstance.h"
#include "../../Creatures/Vehicles/Vehicle.h"
#include "../../State/VehicleStateMachine.h"
#include "../../State/VehicleState.h"


UHorseAnimInstance::UHorseAnimInstance()
{
}

void UHorseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();

	if(IsValid(pawn) == false)
		return;

	auto Vehicle = Cast<AVehicle>(pawn);

	if(Vehicle == nullptr)
		return;

	IsDash = Vehicle->GetIsDash();
	auto StateMachine = Vehicle->GetStateMachine();

	if(StateMachine == nullptr)
		return;

	VehicleState = StateMachine->GetState()->StateEnum;


}
