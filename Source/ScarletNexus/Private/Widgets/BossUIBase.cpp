// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BossUIBase.h"
#include "Materials/MaterialParameterCollection.h"

/*FName UBossUIBase::GetParameterName()
{
	static ConstructorHelpers::FObjectFinder<UMaterialParameterCollection> MPCAsset(TEXT("/Game/Resources/UI/Enemy/Boss/Materials/MPC_Health.MPC_Health"));
	if (MPCAsset.Succeeded())
	{
		MaterialParameterCollection = MPCAsset.Object;
		TArray<FName> ParamArray = MaterialParameterCollection->GetScalarParameterNames();

		for ( FName ParamName : ParamArray )
		{
			if (ParamName != "BossHPPercent")
			{
				continue;
			}
			else
			{
				return ParamName;
			}
		}
	}
	return FName();
}*/
