// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter/BossEnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseGameplayTags.h"
#include "DataAsset/DataAsset_StartupBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseDebugHelper.h"

ABossEnemyCharacter::ABossEnemyCharacter()
{

	MainBody= GetMesh();
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainBodyMesh(TEXT("/Game/Resources/Enemies/EM300/Model/SK_em0300.SK_em0300"));
	if (MainBodyMesh.Succeeded())
	{
		MainBody->SetSkeletalMesh(MainBodyMesh.Object);
	}

	MainCapsule = GetCapsuleComponent();
	const float CapsuleRadius = 300.0f;
	const float CapsuleHalfHeight = 300.0f;
	MainCapsule->InitCapsuleSize(CapsuleRadius, CapsuleHalfHeight);

	
	HitboxCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitboxCapsule"));
	HitboxCapsule->InitCapsuleSize(CapsuleRadius, CapsuleHalfHeight);
	HitboxCapsule->SetupAttachment(MainBody, FName("Hips"));

	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	
	Movement = GetCharacterMovement();
	Movement->bUseControllerDesiredRotation = false;
	Movement->bOrientRotationToMovement = true;

	BaseAbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	
}

FVector ABossEnemyCharacter::GetTargetVector()
{
	FVector TargetVector = (MainBody->GetBoneLocation("Water1") + FVector(0.f, 0.f, 1200.f));
	return TargetVector;
}

