// Fill out your copyright notice in the Description page of Project Settings.


#include "SectorSystem/BaseSectorWall.h"

#include "BaseDebugHelper.h"

// Sets default values
ABaseSectorWall::ABaseSectorWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(Root);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshAsset.Succeeded())
	{
		StaticMesh->SetStaticMesh(MeshAsset.Object);
	}
}
// Called when the game starts or when spawned
void ABaseSectorWall::BeginPlay()
{
	Super::BeginPlay();
	//Debug::Print("ABaseSectorWall::BeginPlay");
}

