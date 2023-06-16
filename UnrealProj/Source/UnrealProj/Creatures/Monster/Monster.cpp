#include "Monster.h"
#include "../../AI/MonsterAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "../../Stat/MonsterStatComponent.h"
#include "../../Animations/Monster/MonsterAnimInstance.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetMesh()->SetCollisionProfileName("NoCollision");
	auto Movement = Cast<UCharacterMovementComponent>(GetMovementComponent());
	Movement->MaxWalkSpeed = 200.f;
	StatComponent = CreateDefaultSubobject<UMonsterStatComponent>(TEXT("StatComponent"));
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	AnimInst = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AMonster::GetObjectName()
{
	FString MyName = GetActorNameOrLabel();
	int StartIndex = 3; // BP_
	int Count = MyName.Len() - 2;
	MyName = MyName.Mid(StartIndex, Count);
	return MyName;
}

void AMonster::AttackTarget(AMyPlayer* Target)
{
	AnimInst->PlayAttackMontage();
}

float AMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	
	auto AIController = Cast<AMonsterAIController>(GetController());
	AIController->StopAI();
	AnimInst->PlayDamagedMontage();

	return Damage;
}


