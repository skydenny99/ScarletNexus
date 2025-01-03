// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PsychokineticPropBase.h"
#include "Components/WidgetComponent.h"

#include "BaseDebugHelper.h"

// Sets default values
APsychokineticPropBase::APsychokineticPropBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InterectComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InterectComponent"));
	InterectComponent->SetupAttachment(RootComponent);
	InterectComponent->SetRelativeLocation(FVector::ZeroVector);
	InterectComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

void APsychokineticPropBase::DissolveProp()
{
	Debug::Print("DissolveProp");
	Destroy();
}


