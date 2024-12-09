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
	// ¸ÞÀÎ ¹Ùµð ½ºÄÌ·¹Å» ¸Þ½Ã
	MainBody = GetMesh();
	MainBody->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainBodyMesh (TEXT("/Game/Resources/Characters/CH0300/CH300_Base.CH300_Base"));
	if (MainBodyMesh.Succeeded())
	{
		MainBody->SetSkeletalMesh(MainBodyMesh.Object);
	}

	// ¾Æ¿ô¶óÀÎ ½ºÄÌ·¹Å» ¸Þ½Ã
	OutLineBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("OutLine"));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> OutlineMesh(TEXT("/Game/Resources/Characters/CH0300/CH300_Outline.CH300_Outline"));
	if (OutlineMesh.Succeeded())
	{
		OutLineBody->SetSkeletalMesh(OutlineMesh.Object);
		OutLineBody->SetupAttachment(MainBody);
		OutLineBody->SetLeaderPoseComponent(MainBody);
	}

	// ¹«±â ¸ÞÀÎ
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("/Game/Resources/Weapons/WP0300/WP300_Base.WP300_Base"));
	if (WeaponMesh.Succeeded())
	{
		Weapon->SetSkeletalMesh(WeaponMesh.Object);
		Weapon->SetupAttachment(MainBody, FName("RightWeapon"));
		// Weapon->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	}

	// ¹«±â ¾Æ¿ô¶óÀÎ
	OutLineWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("OutLineWeapon"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> OutlineWeaponMesh(TEXT("/Game/Resources/Weapons/WP0300/WP300_Outline.WP300_Outline"));
	if (OutlineWeaponMesh.Succeeded())
	{
		OutLineWeapon->SetSkeletalMesh(OutlineWeaponMesh.Object);
		OutLineWeapon->SetupAttachment(Weapon);
		OutLineWeapon->SetLeaderPoseComponent(Weapon);
	}



	// ¸ÞÀÎ Ä¸½¶ ÄÄÆ÷³ÍÆ®
	MainCapsule = GetCapsuleComponent();
	const float CapsuleRadius = 42.f;
	const float CapsuleHalfHeight = 96.f;
	MainCapsule->InitCapsuleSize(CapsuleRadius, CapsuleHalfHeight);

	// È÷Æ®¹Ú½º Ä¸½¶ ÄÄÆ÷³ÍÆ®
	HitboxCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitboxCapsule"));
	HitboxCapsule->InitCapsuleSize(CapsuleRadius, CapsuleHalfHeight);
	HitboxCapsule->SetupAttachment(MainBody, FName("Hips"));
	// HitboxCapsule->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Ä³¸¯ÅÍ ¹«ºê¸ÕÆ® ÄÄÆ÷³ÍÆ®
	Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = true;


	// ¾îºô¸®Æ¼
	BaseAbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("AbilitySystemComponent"));



}


