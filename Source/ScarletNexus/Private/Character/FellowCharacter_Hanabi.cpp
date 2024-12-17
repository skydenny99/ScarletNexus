// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FellowCharacter_Hanabi.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseGameplayTags.h"
#include "DataAsset/DataAsset_StartupBase.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "BaseDebugHelper.h"





AFellowCharacter_Hanabi::AFellowCharacter_Hanabi()
{
	

	
	// ���� �ٵ� ���̷�Ż �޽�
	MainBody = GetMesh();
	MainBody->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainBodyMesh (TEXT("/Game/Resources/Characters/CH0300/CH300_Base.CH300_Base"));
	if (MainBodyMesh.Succeeded())
	{
		MainBody->SetSkeletalMesh(MainBodyMesh.Object);
	}

	// �ƿ����� ���̷�Ż �޽�
	OutLineBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("OutLine"));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> OutlineMesh(TEXT("/Game/Resources/Characters/CH0300/CH300_Outline.CH300_Outline"));
	if (OutlineMesh.Succeeded())
	{
		OutLineBody->SetSkeletalMesh(OutlineMesh.Object);
		OutLineBody->SetupAttachment(MainBody);
		OutLineBody->SetLeaderPoseComponent(MainBody);
	}

	
	

	// ���� ĸ�� ������Ʈ
	MainCapsule = GetCapsuleComponent();
	const float CapsuleRadius = 42.f;
	const float CapsuleHalfHeight = 96.f;
	MainCapsule->InitCapsuleSize(CapsuleRadius, CapsuleHalfHeight);

	// ��Ʈ�ڽ� ĸ�� ������Ʈ
	HitboxCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitboxCapsule"));
	HitboxCapsule->InitCapsuleSize(CapsuleRadius, CapsuleHalfHeight);
	HitboxCapsule->SetupAttachment(MainBody, FName("Hips"));
	// HitboxCapsule->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// ĳ���� �����Ʈ ������Ʈ
	Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = true;


	// �����Ƽ
	BaseAbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("AbilitySystemComponent"));



}


