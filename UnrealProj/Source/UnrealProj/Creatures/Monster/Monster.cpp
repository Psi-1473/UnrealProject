#include "Monster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "../../Stat/MonsterStatComponent.h"
#include "../../Animations/Monster/MonsterAnimInstance.h"
#include "Components/SceneComponent.h"
#include "../../TextRender/DamageText.h"
#include "../../MyGameInstance.h"
#include "../Player/MyPlayer.h"
#include "../../Stat/PlayerStatComponent.h"
#include "../../Inventory/Inventory.h"
#include "../../AI/MonsterAIController.h"
#include "Kismet/GameplayStatics.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;
	StatComponent = CreateDefaultSubobject<UMonsterStatComponent>(TEXT("StatComponent"));
	DamageTextComp = CreateDefaultSubobject<USceneComponent>(TEXT("DamageTextComponent"));
	DamageTextComp->SetRelativeLocation(FVector(50.f, 0.f, 0.f));

	
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionProfileName("NoCollision");
	auto Movement = Cast<UCharacterMovementComponent>(GetMovementComponent());
	Movement->MaxWalkSpeed = 200.f;
	// 메쉬 - 속도만 세팅
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// 애니메이션 인스턴스만 가져옴
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AMonster::GetObjectName()
{
	FString MyName = GetClass()->GetName(); // BP_Zombie_C
	int StartIndex = 3; // BP_ 이후 첫 글자의 Index가 3
	int Count = MyName.Len() - StartIndex - 2; // Len - StartIndex = Zombie_C, -2를 더 해주면 Zombie
	MyName = MyName.Mid(StartIndex, Count); // Zombie
	return MyName;
}


float AMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return Damage;
}


void AMonster::DestroyObject()
{
	
}




void AMonster::PlayHitSound(USoundWave* Sound)
{
	if (Sound == nullptr)
		return;
	UGameplayStatics::PlaySound2D(GetWorld(), Sound);
}

void AMonster::PopupDamageText(float Damage)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	auto DamageText = GetWorld()->SpawnActor<ADamageText>(ADamageText::StaticClass(),
		GetActorLocation() + DamageTextComp->GetRelativeLocation(),
		DamageTextComp->GetRelativeRotation(),
		SpawnParams);

	DamageText->SetDamageText(Damage);
}


