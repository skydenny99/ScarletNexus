// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PsychokineticPropBase.h"

#include "BaseDebugHelper.h"

// Sets default values
APsychokineticPropBase::APsychokineticPropBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void APsychokineticPropBase::DeactivateControl()
{
}

void APsychokineticPropBase::DissolveProp()
{
	Debug::Print("DissolveProp");
	Destroy();
}


