// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Core/EnemyCore.h"

#include "Components/BoxComponent.h"


// Sets default values
AEnemyCore::AEnemyCore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	MainMesh = CreateDefaultSubobject<USkeletalMeshComponent>("MainMesh");
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CoreAsset(TEXT("/Game/Resources/Enemies/EnemyCore/EnemyCore.EnemyCore"));
	if (CoreAsset.Succeeded())
	{
		MainMesh->SetSkeletalMesh(CoreAsset.Object);
		RootComponent = MainMesh;
	}
	CoreCollsionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CoreCollsionBox"));
	CoreCollsionBox->SetupAttachment(RootComponent);
	CoreCollsionBox->SetBoxExtent(FVector(20.0f));
	CoreCollsionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}
