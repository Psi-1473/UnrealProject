

#include "DamageText.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetMathLibrary.h"

ADamageText::ADamageText()
{
	PrimaryActorTick.bCanEverTick = true;
	
	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TEXTRENDER"));
	RootComponent = TextRender;
	//�ؽ�Ʈ ���� ����

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

	// ī�޶� �Ĵٺ��� �ϱ�


	//1. �ٶ� ���� ���ϱ�
	//FRotator Rot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
	// 2. �ٶ󺸰� �ϱ�
	//SetActorRotation(Rot);

}

void ADamageText::Init()
{
}

