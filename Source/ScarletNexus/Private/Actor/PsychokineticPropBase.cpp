// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PsychokineticPropBase.h"
#include "Components/WidgetComponent.h"

#include "BaseDebugHelper.h"
#include "Components/BoxComponent.h"

// Sets default values
APsychokineticPropBase::APsychokineticPropBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);

	
	InterectComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InterectComponent"));
	InterectComponent->SetupAttachment(BoxComponent);
	
	InterectComponent->SetRelativeLocation(FVector::ZeroVector);
	InterectComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

void APsychokineticPropBase::DissolveProp()
{
	//Debug::Print("DissolveProp");
	Destroy();
}


