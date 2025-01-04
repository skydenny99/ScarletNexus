// Fill out your copyright notice in the Description page of Project Settings.


#include "SectorSystem/BaseSector.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SectorSystem/BaseSectorWall.h"
#include "Character/Character_Kasane.h"

#include "BaseDebugHelper.h"
#include "ScarletNexusGameMode.h"
#include "Components/TargetTrackingSpringArmComponent.h"
#include "Field/FieldSystemNodes.h"

// Sets default values
ABaseSector::ABaseSector()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Center = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Center;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(Center);
	TriggerBox->SetBoxExtent(FVector(1200.0f, 1200.0f, 1200.0f));
	
	TriggerBox->SetGenerateOverlapEvents(true);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this,&ABaseSector::OnOverlap);

	for (int i = 0; i < 9; i++)
	{
		FString ComName = "SpawnPoint";
		ComName.AppendInt(i);
		USceneComponent* LocalPos = CreateDefaultSubobject<USceneComponent>(*ComName);
		LocalPos->SetupAttachment(Center);
		LocalPos->SetRelativeLocation(FVector(0.0f,0.0f,30.0f));
		
		SpawnPos.Add(LocalPos);
	}
}

// Called when the game starts or when spawned
void ABaseSector::BeginPlay()
{
	Super::BeginPlay();
	SpawnWall();
	
	DrawDebugBox(GetWorld(),TriggerBox->GetComponentLocation(),TriggerBox->GetScaledBoxExtent(),FColor::Green,true);
}

void ABaseSector::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacter_Kasane>(OtherActor) != nullptr)
	{
		Debug::Print("OnOverlap");

		ToggleWall();
		SpawnEnemy(StageNum);

		TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ABaseSector::SpawnWall()
{
	const FVector Location = FVector(Radius, 0, 750);
	const float Radian= (180.0f/Divide) / (180.0f/PI);
	const float Width = 2*Radius*FMath::Tan(Radian);
	
	for (int i = 0; i < Divide; i++)
	{
		const int Angle = i * 360.0f / Divide;
		const FVector TargetRelativeLoc = UKismetMathLibrary::RotateAngleAxis(Location, static_cast<float>(Angle), FVector::UpVector);
		const FRotator TargetRelativeRotate = FRotator(0.0f, static_cast<float>(Angle),0.0f);
		const FVector Scale = FVector(0.01f,0.01* Width,15.0f);

		UChildActorComponent* ChildActorComp = Cast<UChildActorComponent>(AddComponentByClass(UChildActorComponent::StaticClass(), true, FTransform(), false));
		ChildActorComp->SetChildActorClass(ABaseSectorWall::StaticClass());
		ChildActorComp->CreateChildActor();
		ChildActorComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		ABaseSectorWall* ChildActor = Cast<ABaseSectorWall>(ChildActorComp->GetChildActor());
		ChildActor->GetStaticMesh()->SetRelativeLocation(TargetRelativeLoc);
		ChildActor->GetStaticMesh()->SetRelativeRotation(TargetRelativeRotate);
		ChildActor->GetStaticMesh()->SetWorldScale3D(Scale);
		ChildActor->GetStaticMesh()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
		ChildActor->GetStaticMesh()->SetMaterial(0, WallMaterial);

		WallArray.Add(ChildActor);
	}
	ToggleWall();
}

void ABaseSector::ToggleWall()
{
	if (bIsActive == false)
	{
		Debug::Print("ActivateWall");
		for (int i = 0; i < WallArray.Num(); i++)
		{
			WallArray[i]->GetStaticMesh()->SetHiddenInGame(false);
			WallArray[i]->GetStaticMesh()->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		}
		bIsActive = true;
	}
	else
	{
		Debug::Print("UnActivateWall");
		for (int i = 0; i < WallArray.Num(); i++)
		{
			WallArray[i]->GetStaticMesh()->SetHiddenInGame(true);
			WallArray[i]->GetStaticMesh()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
		}
		bIsActive = false;
	}
}

void ABaseSector::SpawnEnemy(const int32 Stage)
{
	TArray<FStageInfo*> StageInfos;
	StageInfoTable->GetAllRows("", StageInfos);
	const FStageInfo* TargetStageInfo = StageInfos[Stage];
	ACharacter_Kasane* Kasane = Cast<ACharacter_Kasane>( UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	for (auto StageInfo : TargetStageInfo->SpawnEnemyInTargetPos)
	{
		Debug::Print(StageInfo.Value->GetName());
		AActor* L_Enemy = GetWorld()->SpawnActor<AActor>(StageInfo.Value,SpawnPos[StageInfo.Key]->GetComponentTransform());
		if (L_Enemy)
		{
			L_Enemy->OnDestroyed.AddDynamic(this,&ABaseSector::OnRemoveEnemy);
			Enemies.Add(L_Enemy);
			if (Kasane)
			{
				L_Enemy->OnDestroyed.AddDynamic(Kasane->GetTargetTrackingComponent(),&UTargetTrackingSpringArmComponent::OnEnemyDead);
			}
		}
		
	}
	if (Kasane)
	{
		Kasane->GetTargetTrackingComponent()->SetFoundTargets(Enemies);
	}

	if (Stage == StageInfos.Num() - 1)
	{
		if (auto Mode = Cast<AScarletNexusGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			Mode->OnFinalStage();
		}
	}
}

inline void ABaseSector::OnRemoveEnemy(AActor* DestroyedActor)
{
	Debug::Print("OnRemoveEnemy");
	
	Enemies.Remove(DestroyedActor);
	if (Enemies.IsEmpty())
	{
		NextStage();
	}
}

void ABaseSector::NextStage()
{
	Debug::Print("NextStage");
	StageNum++;
	if (StageNum == 4)
	{
		Debug::Print("EndStage");
		ToggleWall();
		return;
	}
	SpawnEnemy(StageNum);
}


/*
// Called every frame
void ABaseSector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/

