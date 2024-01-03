// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchTarget.h"
#include "../../AI/MonsterAIController.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../State/CharacterState.h"

UBTService_SearchTarget::UBTService_SearchTarget()
{
	NodeName = TEXT("SearchTarget");
	Interval = 1.0f;
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
		return;

	UWorld* World = CurrentPawn->GetWorld();
	FVector Center = CurrentPawn->GetActorLocation();
	float SearchRadius = 500.f;

	if (World == nullptr)
		return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams QueryParams(NAME_None, false, CurrentPawn);


	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(SearchRadius),
		QueryParams);


	if (bResult)
	{
		for (auto& OverlapResult : OverlapResults)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Hit")); 
			AMyPlayer* Player = Cast<AMyPlayer>(OverlapResult.GetActor());
			if (Player)
			{
				if (Player->GetState() == Player->GetSpecificState(STATE::DEAD))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
					continue;
				}
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), Player);
				//DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Green, false, 0.2f);
				OwnerComp.GetAIOwner()->GetCharacter()->GetCharacterMovement()->StopActiveMovement();
				
				return;
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
		//DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Red, false, 0.2f);
	}
	

}
