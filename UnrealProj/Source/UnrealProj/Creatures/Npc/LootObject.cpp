
#include "LootObject.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "../../MyGameInstance.h"
#include "../../DEFINE.h"
#include "../../Managers/UIManager.h"
#include "../../Managers/QuestManager.h"
#include "../../Widgets/Popup/Widget_Looting.h"
#include "../Player/MyPlayer.h"

// Sets default values
ALootObject::ALootObject()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBox"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));

	Mesh->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	Mesh->SetRelativeRotation(FRotator(0.f, -90.f, -0.f));

	InteractBox->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	InteractBox->SetCollisionProfileName("InteractBox");

	CapsuleComponent->SetCapsuleHalfHeight(88.f);
	CapsuleComponent->SetCapsuleRadius(34.f);

	RootComponent = CapsuleComponent;
	InteractBox->SetupAttachment(RootComponent);
	Mesh->SetupAttachment(RootComponent);

	InteractBox->OnComponentBeginOverlap.AddDynamic(this, &IInteractable::OnOverlapBegin);
	InteractBox->OnComponentEndOverlap.AddDynamic(this, &IInteractable::OnOverlapEnd);
}


void ALootObject::BeginPlay()
{
	AActor::BeginPlay();
	
}


void ALootObject::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);

}

void ALootObject::Interact(AMyPlayer* Player)
{
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	auto UI = GInstance->GetUIMgr()->PopupUI(GetWorld(), UIType::Looting);
	auto LootUI = Cast<UWidget_Looting>(UI);
	if(LootUI != nullptr)
		LootUI->SetTime(Time, this);
	InteractingPlayer = Player;
	InteractingPlayer->SetState(STATE::LOOT);
}

void ALootObject::LootEnd()
{
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	GInstance->GetUIMgr()->CloseUI((int)UIType::Looting);
	GInstance->GetQuestMgr()->CheckQuestTarget(QUEST_INVESTIGATE, Id, InteractingPlayer);
	InteractingPlayer->SetState(STATE::IDLE);
	InteractingPlayer = nullptr;

	Destroy();
	// 진행 중인 퀘스트가 있으면 진척도 올리기
}

void ALootObject::LootCancle()
{

}

