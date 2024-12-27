// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService/BTS_OrientToTargetActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseDebugHelper.h"


UBTS_OrientToTargetActor::UBTS_OrientToTargetActor()
{
	NodeName = "BTS_OrientToTargetActor";
	INIT_SERVICE_NODE_NOTIFY_FLAGS();

	RotationInterpSpeed = 5.0f;
	Interval = 0.f;
	RandomDeviation = 0.f;

	InTargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetActorKey), AActor::StaticClass());

	
}

void UBTS_OrientToTargetActor::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		InTargetActorKey.ResolveSelectedKey(*BBAsset);
	}

	
}

void UBTS_OrientToTargetActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UObject* ActorObject =  OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetActorKey.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(ActorObject);

	
	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (OwningPawn && TargetActor)
	{
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(OwningPawn->GetActorLocation(), TargetActor->GetActorLocation());

		// 2. 현재 회전 값 가져오기
		FRotator CurrentRot = OwningPawn->GetActorRotation();
		
		const FRotator TargetRot = FMath::RInterpTo(CurrentRot, FRotator(CurrentRot.Pitch, LookAtRot.Yaw, LookAtRot.Roll),DeltaSeconds, RotationInterpSpeed);

		OwningPawn->SetActorRotation(TargetRot);
	}
	
}


