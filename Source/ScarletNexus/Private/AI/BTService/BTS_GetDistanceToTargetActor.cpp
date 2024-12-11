// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService/BTS_GetDistanceToTargetActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseDebugHelper.h"


UBTS_GetDistanceToTargetActor::UBTS_GetDistanceToTargetActor()
{
	NodeName = TEXT("BTS_GetDistanceToTargetActor");

	INIT_SERVICE_NODE_NOTIFY_FLAGS();

	
}

void UBTS_GetDistanceToTargetActor::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		InTargetActorKey.ResolveSelectedKey(*BBAsset);
	}
}

void UBTS_GetDistanceToTargetActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UObject* TargetActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetActorKey.SelectedKeyName);

	AActor* TargetActor = Cast<AActor>(TargetActorObject);

	// 유효성 검사
	if (TargetActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("TargetActor is null"));
		return;
	}

	// AI 소유자를 통해 Pawn을 얻음
	APawn* ControlledPawn = OwnerComp.GetAIOwner() ? OwnerComp.GetAIOwner()->GetPawn() : nullptr;

	if (ControlledPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ControlledPawn is null"));
		return;
	}

	// 거리 계산
	float Distance = ControlledPawn->GetDistanceTo(TargetActor);

	// 결과를 블랙보드에 저장하거나 디버깅 로그 출력
	// Debug::Print(TEXT("Distance to target actor: "), Distance);
	
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(OutDistanceKey.SelectedKeyName, Distance);
	
}
