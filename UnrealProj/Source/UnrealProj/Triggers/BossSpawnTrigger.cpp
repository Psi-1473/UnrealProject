// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSpawnTrigger.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../Creatures/Monster/BossMonster.h"
#include "../Managers/UIManager.h"
#include "../DEFINE.h"
#include "../MyGameMode.h"
#include "../MyGameInstance.h"
#include "Components/BoxComponent.h"
#include "LevelSequencePlayer.h"
#include "UObject/SoftObjectPath.h"
#include "Kismet/GameplayStatics.h"
#include "../Widgets/Popup/Widget_BossHpBar.h"


ABossSpawnTrigger::ABossSpawnTrigger(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<ABossMonster> BOSS(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/Creatures/Enemies/Boss/BP_Sevarog.BP_Sevarog_C'"));
	if (BOSS.Succeeded())
		BossClass = BOSS.Class;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetCollisionProfileName("InteractBox");

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABossSpawnTrigger::OnOverlapBegin);
}

void ABossSpawnTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABossSpawnTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Triger Enter Active"));
	if (bActivated)
		return;

	if (OtherActor)
	{
		auto Player = Cast<AMyPlayer>(OtherActor);
		if (Player)
		{
			HideWidget();
			EnteredPlayer = Player;
			GetWorldTimerManager().SetTimer(SpawnBossTimer, this, &ABossSpawnTrigger::SpawnBoss, 2.f, false);
			bActivated = true;
			UE_LOG(LogTemp, Warning, TEXT("Player Enter!"));

			FStringAssetReference SequenceName("/Script/LevelSequence.LevelSequence'/Game/11_LevelSequence/SevarogSequence.SevarogSequence'");
			ULevelSequence* Asset = Cast<ULevelSequence>(SequenceName.TryLoad());
			
			FMovieSceneSequencePlaybackSettings Settings;
			ALevelSequenceActor* SequenceActor = this;
			ULevelSequencePlayer* SevarogSequence = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), Asset, Settings, SequenceActor);
			SevarogSequence->OnFinished.AddDynamic(this, &ABossSpawnTrigger::ResetWidget);
			// 1. 시네마틱 재생
			SevarogSequence->Play();
			// 2. 보스 소환
			// 3. 보스 Hp Widget 팝업
			
			
		}
	}
}

void ABossSpawnTrigger::HideWidget()
{
	auto GMode = UGameplayStatics::GetGameMode(GetWorld());
	auto MyGameMode = Cast<AMyGameMode>(GMode);
	MyGameMode->HideHud();
}

void ABossSpawnTrigger::ResetWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("Reset Widget!"));
	auto GMode = UGameplayStatics::GetGameMode(GetWorld());
	auto MyGameMode = Cast<AMyGameMode>(GMode);
	MyGameMode->AppearHud();

	auto GInstance = Cast<UMyGameInstance>(GetGameInstance());
	auto BossHpBar = Cast<UWidget_BossHpBar>(GInstance->GetUIMgr()->PopupUI(GetWorld(), UIType::BossHpBar));
	BossHpBar->BindBoss(Cast<ABossMonster>(SpawnedBoss));
}

void ABossSpawnTrigger::SpawnBoss()
{
	FActorSpawnParameters SpawnParams;
	//SpawnParams.Owner = Cast<AActor>(OwnerMonster);
	//SpawnParams.Instigator = OwnerMonster->GetInstigator();

	FRotator SpawnRot = GetActorRotation();
	FVector SpawnPos = FVector(-15510.f, 850.f, 380.f);

	SpawnedBoss = GetWorld()->SpawnActor<ABossMonster>(
		BossClass,
		SpawnPos,
		SpawnRot,
		SpawnParams);
}


