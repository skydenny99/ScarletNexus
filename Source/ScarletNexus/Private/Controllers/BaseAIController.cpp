// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BaseAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"

#include "Kismet/GameplayStatics.h"


#include "BaseDebugHelper.h"



ABaseAIController::ABaseAIController(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	//SetDefaultSubObjectClass CrowdFollowingComponent
    if (UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
    {
        CrowdFollowingComponent->SetCrowdSimulationState(ECrowdSimulationState::Enabled);
        // Debug::Print(TEXT("CrowdFollowComponent Valid"), FColor::Green);
    }
    else
    {
        //Debug::Print(TEXT("CrowdFollowingComponent 초기화 실패."));
    }
    
    
        

	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));
   
    AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
    
    AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
    
    AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
    
    AISenseConfig_Sight->SightRadius = 3500.0f;
    
    AISenseConfig_Sight->LoseSightRadius = 0.f;
   
    AISenseConfig_Sight->PeripheralVisionAngleDegrees = 180.0f;

    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
    
    AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
    AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ABaseAIController::OnEnemyPerceptionUpdated);

  
    SetGenericTeamId(AITeamId);


    
}

ETeamAttitude::Type ABaseAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
    const APawn* PawnCheck = Cast<const APawn>(&Other);
    const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(PawnCheck->GetController());

    
    if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() != GetGenericTeamId())
    {
        
        return ETeamAttitude::Hostile;
    }

	return ETeamAttitude::Friendly;
}

FGenericTeamId ABaseAIController::GetGenericTeamId() const
{
    return AITeamId;
}

int32 ABaseAIController::GetTeamId()
{
    return static_cast<int32>(AITeamId.GetId());
}

void ABaseAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    // Debug::Print(FString::Printf(TEXT("PerceptionUpdated Call : %s"), *Actor->GetName()),FColor::Blue);
    
    if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
    {
        if (BlackboardComponent->GetValueAsObject(FName("TargetActor")) == nullptr)
        {
            if (Stimulus.WasSuccessfullySensed()&& Actor)
            {
                //Debug::Print((TEXT("OnEnemyPerceptionUpdated Call : %s"), Actor->GetName()),FColor::Red);
                BlackboardComponent->SetValueAsObject(FName(TEXT("TargetActor")), Actor);

                OnEnemyPerceptionUIUpdated.Broadcast();                
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
    
    //Debug::Print(TEXT("BeginPlay Call"),FColor::Red);


    // 블랙보드가 유효하지 않으면 초기화

    ABaseAIController::SetTeamId(1);
    

}


void ABaseAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    
    // if (BTAsset)
    // {
    //     RunBehaviorTree(BTAsset);
    //     Debug::Print(TEXT("BTAsset Set!"),FColor::Blue);
    //     // 블랙보드 타겟 값 세팅
    //     if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
    //     {
    //         // 플레이어 캐릭터 가져오기
    //         APlayerController* PlayerPawn = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    //         if (PlayerPawn)
    //         {
    //             // 블랙보드에 TargetActor로 설정
    //             BlackboardComponent->SetValueAsObject(TEXT("TargetActor"), PlayerPawn);
    //             Debug::Print((TEXT("TargetActor 설정 완료: %s"), *PlayerPawn->GetName()), FColor::Blue);
    //         }
    //         else
    //         {
    //             Debug::Print(TEXT("플레이어 폰을 찾을 수 없습니다."));
    //         }
    //     }
    //     else
    //     {
    //         Debug::Print(TEXT("BlackboardComponent가 유효하지 않습니다."));
    //     }
    //     
    // }
    // else
    // {
    //     Debug::Print(TEXT("BTAsset Error!!!"),FColor::Red);
    // }
    
    
}

void ABaseAIController::SetTeamId(int32 TeamId)
{
    
    SetGenericTeamId(FGenericTeamId(TeamId));
}

