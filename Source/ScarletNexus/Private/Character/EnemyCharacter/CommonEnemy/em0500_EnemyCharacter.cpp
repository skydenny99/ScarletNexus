// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter/CommonEnemy/em0500_EnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseGameplayTags.h"
#include "DataAsset/DataAsset_StartupBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseDebugHelper.h"

Aem0500_EnemyCharacter::Aem0500_EnemyCharacter()
{
	
	MainBody= GetMesh();
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainBodyMesh(TEXT("/Game/Resources/Enemies/EM500/EM500_Base.EM500_Base"));
	if (MainBodyMesh.Succeeded())
	{
		MainBody->SetSkeletalMesh(MainBodyMesh.Object);
	}

	MainCapsule = GetCapsuleComponent();
	const float CapsuleRadius = 80.0f;
	const float CapsuleHalfHeight = 80.0f;
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
