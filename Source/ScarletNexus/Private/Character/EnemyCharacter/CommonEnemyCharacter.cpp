// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter/CommonEnemyCharacter.h"

#include "Items/Core/EnemyCore.h"

ACommonEnemyCharacter::ACommonEnemyCharacter()
{
	EnemyCoreChildComponent = CreateDefaultSubobject<UChildActorComponent>(FName("EnemyCore"));
	EnemyCoreChildComponent->SetChildActorClass(AEnemyCore::StaticClass());
	EnemyCoreChildComponent->SetupAttachment(GetMesh(), TEXT("Weak01"));
	EnemyCoreChildComponent->SetRelativeRotation(FRotator(0, 0, -90.f));
}

void ACommonEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	EnemyCoreChildComponent->CreateChildActor();
	EnemyCoreChildComponent->SetHiddenInGame(true);
}

void ACommonEnemyCharacter::ActivateEnemyCore(bool bIsActive)
{
	EnemyCoreChildComponent->SetHiddenInGame(!bIsActive);
}


FVector ACommonEnemyCharacter::GetTargetVector()
{
	FVector TargetVector = (MainBody->GetBoneLocation("Target"));
	return TargetVector;
}
