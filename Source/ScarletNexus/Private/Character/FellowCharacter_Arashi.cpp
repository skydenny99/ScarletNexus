// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FellowCharacter_Arashi.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseGameplayTags.h"
#include "DataAsset/DataAsset_StartupBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseDebugHelper.h"




AFellowCharacter_Arashi::AFellowCharacter_Arashi()
{

	
	MainBody = GetMesh();
	MainBody->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainBodyMesh(TEXT("/Game/Resources/Characters/CH1000/CH1000_Base.CH1000_Base"));
	if (MainBodyMesh.Succeeded())
	{
		MainBody->SetSkeletalMesh(MainBodyMesh.Object);
	}

	
	OutLineBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("OutLine"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> OutlineMesh(TEXT("/Game/Resources/Characters/CH1000/CH1000_Outline.CH1000_Outline"));
	if (OutlineMesh.Succeeded())
	{
		OutLineBody->SetSkeletalMesh(OutlineMesh.Object);
		OutLineBody->SetupAttachment(MainBody);
		OutLineBody->SetLeaderPoseComponent(MainBody);
	}

	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("/Game/Resources/Weapons/WP1000/WP1000_Base.WP1000_Base"));
	if (WeaponMesh.Succeeded())
	{
		Weapon->SetSkeletalMesh(WeaponMesh.Object);
		Weapon->SetupAttachment(MainBody, FName("LeftWeapon"));
		// Weapon->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	}

	
	OutLineWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("OutLineWeapon"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> OutlineWeaponMesh(TEXT("/Game/Resources/Weapons/WP1000/WP1000_Outline.WP1000_Outline"));
	if (OutlineWeaponMesh.Succeeded())
	{
		OutLineWeapon->SetSkeletalMesh(OutlineWeaponMesh.Object);
		OutLineWeapon->SetupAttachment(Weapon);
		OutLineWeapon->SetLeaderPoseComponent(Weapon);
	}



	
	MainCapsule = GetCapsuleComponent();
	const float CapsuleRadius = 42.f;
	const float CapsuleHalfHeight = 96.f;
	MainCapsule->InitCapsuleSize(CapsuleRadius, CapsuleHalfHeight);

	
	HitboxCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitboxCapsule"));
	HitboxCapsule->InitCapsuleSize(CapsuleRadius, CapsuleHalfHeight);
	HitboxCapsule->SetupAttachment(MainBody, FName("Hips"));
	// HitboxCapsule->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));


	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	
	Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = true;


	
	BaseAbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("AbilitySystemComponent"));



}


