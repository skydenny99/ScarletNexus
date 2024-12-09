// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BaseAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"



#include "BaseDebugHelper.h"


ABaseAIController::ABaseAIController(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	//SetDefaultSubobjectClass로 CrowdFollowingComponent 사용
	if (UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		Debug::Print(TEXT("CrowdFollowComponent Vaild"), FColor::Green);
	}

	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));

    //적 감지
    AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
    //아군 감지
    AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
    //중립 감지
    AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
    //시아 반경설정
    AISenseConfig_Sight->SightRadius = 2000.0f;
    //대상을 잃는 시아 범위 설정
    AISenseConfig_Sight->LoseSightRadius = 0.f;
    //주변 시아각
    AISenseConfig_Sight->PeripheralVisionAngleDegrees = 180.0f;

    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
    //센서 설정
    AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
    AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
    // AIPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ABaseAIController::OnEnemyPeceptionUpdated);

    //팀아이디 부여 -> 하위 에서 다시 정의
    // SetGenericTeamId(FGenericTeamId(0));




}

ETeamAttitude::Type ABaseAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	return ETeamAttitude::Type();
}
