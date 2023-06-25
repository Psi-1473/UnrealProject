#include "SkillRangeActor.h"

ASkillRangeActor::ASkillRangeActor()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootComponent = Root;
	Mesh->SetupAttachment(Root);
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

	Mesh->SetStaticMesh(StaticMesh);
	Mesh->SetRelativeScale3D(FVector(Size, Size, 0.01));
}


//ASkillRangeActor* ASkillRangeActor::MakeCircleRange(float Radius)
//{
//	float Size = Radius / 2;
//	FString Directory = TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'");
//
//	ASkillRangeActor* Range = NewObject<ASkillRangeActor>();
//	UStaticMesh* StaticMesh = LoadObject<UStaticMesh>(NULL, *Directory, NULL, LOAD_None, NULL);
//
//	Range->Mesh->SetStaticMesh(StaticMesh);
//	Range->Mesh->SetRelativeScale3D(FVector(Size, Size, 0.01));
//	
//	return Range;
//}