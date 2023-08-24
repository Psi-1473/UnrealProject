#include "SkillRangeActor.h"
#include "Math/Vector.h"
#include "Components/DecalComponent.h"

ASkillRangeActor::ASkillRangeActor()
{
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UMaterial> Mat(TEXT("/Script/Engine.Material'/Game/02_Blueprints/DecalMat.DecalMat'"));

	if (Mat.Succeeded())
		Material = Mat.Object;

}

void ASkillRangeActor::BeginPlay()
{
	Super::BeginPlay();

}


void ASkillRangeActor::MakeThisToCircle(float Radius)
{
	float Size = Radius * 2;
	FString Directory = TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'");
	UStaticMesh* StaticMesh = LoadObject<UStaticMesh>(NULL, *Directory, NULL, LOAD_None, NULL);
	StaticMesh->SetMaterial(0, Material);
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
