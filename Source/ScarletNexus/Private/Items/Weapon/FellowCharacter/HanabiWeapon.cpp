// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon/FellowCharacter/HanabiWeapon.h"
#include "Components/BoxComponent.h"
#include "BaseDebugHelper.h"

AHanabiWeapon::AHanabiWeapon()
{
	// 메인
	// WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponAsset(TEXT("/Game/Resources/Weapons/WP0300/WP300_Base.WP300_Base"));
	if (WeaponAsset.Succeeded())
	{
		WeaponMesh -> SetSkeletalMesh(WeaponAsset.Object);
		RootComponent = WeaponMesh;
		
	}
	// 아웃라인
	// OutLineWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("OutlineWeaponMesh"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> OutlineWeaponAsset(TEXT("/Game/Resources/Weapons/WP0300/WP300_Outline.WP300_Outline"));
	if (OutlineWeaponAsset.Succeeded())
	{
		OutLineWeaponMesh->SetSkeletalMesh(OutlineWeaponAsset.Object);
		OutLineWeaponMesh->SetupAttachment(WeaponMesh);
		OutLineWeaponMesh->SetLeaderPoseComponent(WeaponMesh);
	}
	

	
	
}
