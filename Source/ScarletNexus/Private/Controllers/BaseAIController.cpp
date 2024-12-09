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
	//SetDefaultSubobjectClass�� CrowdFollowingComponent ���
	if (UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		Debug::Print(TEXT("CrowdFollowComponent Vaild"), FColor::Green);
	}

	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));

    //�� ����
    AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
    //�Ʊ� ����
    AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
    //�߸� ����
    AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
    //�þ� �ݰ漳��
    AISenseConfig_Sight->SightRadius = 2000.0f;
    //����� �Ҵ� �þ� ���� ����
    AISenseConfig_Sight->LoseSightRadius = 0.f;
    //�ֺ� �þư�
    AISenseConfig_Sight->PeripheralVisionAngleDegrees = 180.0f;

    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
    //���� ����
    AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
    AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ABaseAIController::OnEnemyPeceptionUpdated);

    

    //�����̵� �ο� -> ���� ���� �ٽ� ���� �⺻�� 0
    SetGenericTeamId(FGenericTeamId(0));


}

ETeamAttitude::Type ABaseAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
    const APawn* PawnCheck = Cast<const APawn>(&Other);
    const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(PawnCheck->GetController());

    // �� ���̵� ũ�� �� �Ʊ��� 0 ���� �׺��� ŭ
    if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
    {
        // �� �Ǵ�
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

// �����̺�� Ʈ�� �۵�
void ABaseAIController::OnPossess(APawn* InPawn)
{
    if (BTAsset != nullptr)
    {
        RunBehaviorTree(BTAsset);
    }

}

void ABaseAIController::SetTeamId(int32 TeamId)
{
    //�����̵� �ο� -> ���� ���� �ٽ� ����
    SetGenericTeamId(FGenericTeamId(TeamId));
}

