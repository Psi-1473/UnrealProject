

#include "DamageText.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetMathLibrary.h"

ADamageText::ADamageText()
{
	PrimaryActorTick.bCanEverTick = true;
	
	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TEXTRENDER"));
	RootComponent = TextRender;
	//텍스트 렌더 세팅

}

// Called when the game starts or when spawned
void ADamageText::BeginPlay()
{
	Super::BeginPlay();
	FTimerDelegate TimeCallback;
	UE_LOG(LogTemp, Warning, TEXT("DamageText!"));
	TimeCallback.BindLambda(
		[this] {this->Destroy(); 
		GetWorldTimerManager().ClearTimer(DestroyTimerHandle); 
		});
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, TimeCallback, 1.f, false);
	
}

// Called every frame
void ADamageText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 카메라 쳐다보게 하기


	//1. 바라볼 방향 정하기
	//FRotator Rot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
	// 2. 바라보게 하기
	//SetActorRotation(Rot);

}

void ADamageText::Init()
{
}

