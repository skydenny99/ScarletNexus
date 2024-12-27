// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WidgetBase.h"

#include "Components/UI/EnemyUIComponent.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/PlayerUIComponent.h"
#include "Interfaces/PawnUIInterface.h"

void UWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UPlayerUIComponent* PlayerUIComponent = PawnUIInterface->GetPlayerUIComponent())
		{
			BP_OnOwningPlayerUIComponentInitialized(PlayerUIComponent);
			OnOwningPlayerUIComponentInitialized(PlayerUIComponent);
		}
	}
}

void UWidgetBase::OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const
{
	//override
}

void UWidgetBase::OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* EnemyUIComponent) const
{
	//override
}

void UWidgetBase::OnOwningPropUIComponentInitialized(UPropUIComponent* PropUIComponent) const
{
	//override
}

void UWidgetBase::InitEnemyCreateWidget(AActor* Enemy)
{
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent())
		{
			BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
			OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
		}
	}
}

/*
void UWidgetBase::InitPropCreateWidget(AActor* Prop)
{
	
}
*/
