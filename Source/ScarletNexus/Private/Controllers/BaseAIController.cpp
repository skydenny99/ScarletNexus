// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BaseAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"



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
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ABaseAIController::OnEnemyPeceptionUpdated);

    

    //팀아이디 부여 -> 하위 에서 다시 정의 기본값 0
    SetGenericTeamId(FGenericTeamId(0));


}

ETeamAttitude::Type ABaseAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
    const APawn* PawnCheck = Cast<const APawn>(&Other);
    const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(PawnCheck->GetController());

    // 팀 아이디 크기 비교 아군이 0 적은 그보다 큼
    if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
    {
        // 적 판단
        return ETeamAttitude::Hostile;
    }

	return ETeamAttitude::Friendly;
}

void ABaseAIController::OnEnemyPeceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{

    if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
    {
        if (BlackboardComponent->GetValueAsObject(FName("TargetActor")) == nullptr)
        {
            if (Stimulus.WasSuccessfullySensed()&& Actor)
            {
                BlackboardComponent->SetValueAsObject(FName(TEXT("TargetActor")), Actor);
            }
        }
    }
}

void ABaseAIController::BeginPlay()
{

    Super::BeginPlay();

    if (UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
    {
        CrowdFollowingComponent->SetCrowdSimulationState(bDetourCrowdAvoidence ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);

        switch (DetourCrowdAvoidenceQuality)
        {
        case 1: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);    break;
        case 2: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium); break;
        case 3: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);   break;
        case 4: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);   break;
        default: break;
        }

        CrowdFollowingComponent->SetAvoidanceGroup(1);
        CrowdFollowingComponent->SetGroupsToAvoid(1);
        CrowdFollowingComponent->SetCrowdCollisionQueryRange(CollsionQueryRange);
    }

}

// 비헤이비어 트리 작동
void ABaseAIController::OnPossess(APawn* InPawn)
{
    if (BTAsset != nullptr)
    {
        RunBehaviorTree(BTAsset);
    }

}

void ABaseAIController::SetTeamId(int32 TeamId)
{
    //팀아이디 부여 -> 하위 에서 다시 정의
    SetGenericTeamId(FGenericTeamId(TeamId));
}

