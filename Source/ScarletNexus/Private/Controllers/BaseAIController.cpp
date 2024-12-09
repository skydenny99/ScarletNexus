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
    // AIPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ABaseAIController::OnEnemyPeceptionUpdated);

    //�����̵� �ο� -> ���� ���� �ٽ� ����
    // SetGenericTeamId(FGenericTeamId(0));




}

ETeamAttitude::Type ABaseAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	return ETeamAttitude::Type();
}
