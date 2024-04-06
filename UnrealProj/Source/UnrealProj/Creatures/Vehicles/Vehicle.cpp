#include "Vehicle.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/MeshComponent.h"
#include "../../Managers/ResourceManager.h"
#include "../../MyGameInstance.h"
#include "../Player/MyPlayer.h"
#include "../../State/VehicleStateMachine.h"
#include "../../DEFINE.h"

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

void AVehicle::Spawn()
{
	// Test //
	FString Dir = TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/Creatures/Vehicles/Horse/BP_Horse");
	Dir += FString::FromInt(Id);
	Dir += TEXT(".BP_Horse");
	Dir += FString::FromInt(Id);
	Dir += TEXT("_C'");

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
	
	StateMachine->SetState(VSTATE::MOUNT);
}

void AVehicle::SetOwnerPlayer(AMyPlayer* Player)
{
	OwnerPlayer = Player;
}


