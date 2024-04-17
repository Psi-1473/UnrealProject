#include "Vehicle.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/MeshComponent.h"
#include "../../Managers/ResourceManager.h"
#include "../../MyGameInstance.h"
#include "../Player/MyPlayer.h"
#include "../../State/VehicleStateMachine.h"
#include "VehicleInfo.h"


AVehicle::AVehicle()
{
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	//SetRootComponent(GetMesh());
	Camera->SetupAttachment(RootComponent);
	SpringArm->SetupAttachment(Camera);


	StateMachine = NewObject<UVehicleStateMachine>();

}

void AVehicle::BeginPlay()
{
	Super::BeginPlay();
	SetState(VSTATE::MOUNT);

	// !!! 
	// StateMachine->SetState(VSTATE::MOUNT); �� �����߻�
	// ����
	// 1. ���� �÷��̾� BeginPlay ���� ���� ������ Ŭ������ ������ ��ġ�ϴ� ���� �ƴ�
	// 2. ���ο� Vehicle Ŭ������ ������ �� 1���� ���� �Ҵ��� Ŭ������ ������ ������ ������� Vehicle�� Spawn�� ������
	// 3. �� ���, 2������ ���ο� Vehicle�� �����Ǹ鼭 �����ڸ� �����ϰ� �ٷ� BeginPlay�� ����
	// 4. Vehicle�� �����ڿ��� StateMachine�� �� �Ҵ��ϴµ�, StateMachine�� �����ں��� Vehicle�� BeginPlay�� �� ���� ����� �� ���� (������ �Ҵ��� ���ÿ� �߻��ϱ� ����)
	// 5. StateMachine->SetState(VSTATE::MOUNT); <---- ���⼭ ���� ������ ����
	// StateMachine->SetState(VSTATE::MOUNT)�� Spawn �Լ��� �Űܼ� �ذ�

}

void AVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AVehicle::SetState(VSTATE State)
{
	if(StateMachine == nullptr)
		StateMachine = NewObject<UVehicleStateMachine>();

	StateMachine->SetState(State);
}

void AVehicle::SetInfo(const UVehicleInfo& Info)
{
	Id = Info.GetId();
	Speed = Info.GetSpeed();
	DashSpeed = Info.GetDashSpeed();

	UE_LOG(LogTemp, Warning, TEXT("Vehicle Set Info : %d, %f, %f"), Id, Speed, DashSpeed);
}

void AVehicle::SetOwnerPlayer(TWeakObjectPtr<AMyPlayer> Player)
{
	OwnerPlayer = Player;
}


