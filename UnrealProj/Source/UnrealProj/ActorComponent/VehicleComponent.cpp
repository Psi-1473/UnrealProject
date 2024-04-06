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
	// 1. 탈 것 스폰
	VehicleInUse->Spawn();
	// 2. 플레이어가 탈 것 타는 애니메이션 실행
	OwnerPlayer->GetStateMachine()->SetState(STATE::RIDE);
	//OwnerPlayer->GetAnimInst()->PlayRideAnim();
	// 애니메이션 실행, 애니메이션 끝에 상태 바꾸는 함수 등록
	// 3. 말의 위치랑 플레이어 위치 잘 조절

	// 4. 플레이어 상태 -> 라이딩으로 변경
	// 라이딩 상태에서 할 일
	// 1) 라이딩에 맞게 메인 카메라 변경
	// 2) 움직이면 말을 움직이게 하고 플레이어는 Vehicle을 따라가게만 하기
	
}

void UVehicleComponent::Dismount()
{
	
}


