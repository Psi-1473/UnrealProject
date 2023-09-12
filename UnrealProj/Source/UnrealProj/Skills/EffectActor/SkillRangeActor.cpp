#include "SkillRangeActor.h"
#include "Math/Vector.h"
#include "Components/DecalComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ASkillRangeActor::ASkillRangeActor()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UMaterial> Mat(TEXT("/Script/Engine.Material'/Game/02_Blueprints/DecalMat.DecalMat'"));

	if (Mat.Succeeded())
		Material = Mat.Object;

}

void ASkillRangeActor::BeginPlay()
{
	Super::BeginPlay();

}

void ASkillRangeActor::Tick(float DeltaSeconds)
{
	// 위치 보정하기
	//CorrectPos();
}


void ASkillRangeActor::MakeThisToCircle(float Radius)
{
	float Size = Radius * 2;
	FString Directory = TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'");
	UStaticMesh* StaticMesh = LoadObject<UStaticMesh>(NULL, *Directory, NULL, LOAD_None, NULL);
	//StaticMesh->SetMaterial(0, Material);
}

void ASkillRangeActor::SetRange(AActor* OwnerActor, float Size, float Angle, float TempTime)
{
	SetActorRelativeRotation(FRotator(-90.f, OwnerActor->GetActorRotation().Yaw, 90.f));
	SetActorRelativeScale3D(FVector(1.f, Size, Size));
	UMaterialInstanceDynamic* dynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	dynamicMaterial->SetScalarParameterValue(FName(TEXT("Angle")), Angle);
	GetDecal()->SetDecalMaterial(dynamicMaterial);

	if(TempTime > 0.f)
		GetWorldTimerManager().SetTimer(DestroyTimer, this, &ASkillRangeActor::DestroyThis, TempTime, false);
}

void ASkillRangeActor::MoveRangeActor(FVector Dir, FVector PlayerPos, float MaxDistance)
{
	float Dist = FVector::Distance(GetActorLocation() + Dir, PlayerPos);
	if (Dist >= MaxDistance)
		return;

	SetActorLocation(GetActorLocation() + Dir);
}

void ASkillRangeActor::DestroyThis()
{
	Destroy();
}

void ASkillRangeActor::CorrectPos()
{
	// 1. 방향으로 Trace 쏘기
	FVector StartPos = GetActorLocation();
	FVector DownVector(0.f, 0.f, -1.f);
	FVector UpVector(0.f, 0.f, 1.f);
	float Len = 300.f;
	FVector DownLoc = StartPos + (DownVector * Len);
	FVector UpLoc = StartPos + (UpVector * Len);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes; // 히트 가능한 오브젝트 유형들.
	TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
	ObjectTypes.Add(WorldStatic);

	TArray<AActor*> IgnoreActors; // 무시할 액터들.

	FHitResult HitResult; // 히트 결과 값 받을 변수.

	bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(
		GetWorld(),
		StartPos,
		DownLoc,
		ObjectTypes,
		false,
		IgnoreActors, // 무시할 것이 없다고해도 null을 넣을 수 없다.
		EDrawDebugTrace::ForDuration,
		HitResult,
		true
	);

	if (Result == true)
	{
		FVector Loc(GetActorLocation().X, GetActorLocation().Y, HitResult.GetActor()->GetActorLocation().Z);
		return;
	}


	Result = UKismetSystemLibrary::LineTraceSingleForObjects(
		GetWorld(),
		StartPos,
		UpLoc,
		ObjectTypes,
		false,
		IgnoreActors, // 무시할 것이 없다고해도 null을 넣을 수 없다.
		EDrawDebugTrace::ForDuration,
		HitResult,
		true
	);

	if (Result == true)
	{
		FVector Loc(GetActorLocation().X, GetActorLocation().Y, HitResult.GetActor()->GetActorLocation().Z);
		return;
	}

	
}
