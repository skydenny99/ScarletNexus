// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BrainCrash/BrainCrash_Studio.h"

// Sets default values
ABrainCrash_Studio::ABrainCrash_Studio()
{
	PrimaryActorTick.bCanEverTick = true;

	MainBody = CreateDefaultSubobject<USkeletalMeshComponent>("MainBody");
	
	OutLineBody = CreateDefaultSubobject<USkeletalMeshComponent>("OutLineBody");
	OutLineBody->SetupAttachment(MainBody);
	OutLineBody->SetLeaderPoseComponent(MainBody);
}
