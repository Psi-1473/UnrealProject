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
	// StateMachine->SetState(VSTATE::MOUNT); 가 에러발생
	// 사유
	// 1. 현재 플레이어 BeginPlay 에서 동적 생성한 클래스를 레벨에 배치하는 것이 아닌
	// 2. 새로운 Vehicle 클래스를 스폰한 뒤 1에서 동적 할당한 클래스의 정보를 덮어씌우는 방식으로 Vehicle의 Spawn을 구현함
	// 3. 이 경우, 2번에서 새로운 Vehicle이 스폰되면서 생성자를 실행하고 바로 BeginPlay를 실행
	// 4. Vehicle의 생성자에서 StateMachine을 또 할당하는데, StateMachine의 생성자보다 Vehicle의 BeginPlay가 더 먼저 실행될 수 있음 (스폰과 할당이 동시에 발생하기 떄문)
	// 5. StateMachine->SetState(VSTATE::MOUNT); <---- 여기서 에러 터지는 이유
	// StateMachine->SetState(VSTATE::MOUNT)를 Spawn 함수로 옮겨서 해결

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


