// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SAS/SAS_Studio.h"


// Sets default values
ASAS_Studio::ASAS_Studio()
{
	PrimaryActorTick.bCanEverTick =false;

	MainBody = CreateDefaultSubobject<USkeletalMeshComponent>("MainBody");
	
	OutLineBody = CreateDefaultSubobject<USkeletalMeshComponent>("OutLineBody");
	OutLineBody->SetupAttachment(MainBody);
	OutLineBody->SetLeaderPoseComponent(MainBody);
	

}



