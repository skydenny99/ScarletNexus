// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter/CommonEnemy/em0700_EnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseGameplayTags.h"
#include "DataAsset/DataAsset_StartupBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseDebugHelper.h"
#include "Components/WidgetComponent.h"

Aem0700_EnemyCharacter::Aem0700_EnemyCharacter()
{
	MainBody= GetMesh();
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainBodyMesh(TEXT("/Game/Resources/Enemies/EM700/EM700_Base.EM700_Base"));
	if (MainBodyMesh.Succeeded())
	{
		MainBody->SetSkeletalMesh(MainBodyMesh.Object);
	}

	MainCapsule = GetCapsuleComponent();
	const float CapsuleRadius = 80.0f;
	const float CapsuleHalfHeight = 60.0f;
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
	
	HealthComponent->SetupAttachment(MainBody, FName("Hips"));
	NoticeComponent->SetupAttachment(MainBody, FName("Hips"));
	LockOnComponent->SetupAttachment(MainBody, FName("Hips"));
	BrainCrashComponent->SetupAttachment(MainBody, FName("Hips"));

	
}
