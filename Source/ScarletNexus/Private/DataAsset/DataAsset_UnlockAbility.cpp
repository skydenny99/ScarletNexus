// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/DataAsset_UnlockAbility.h"

bool UDataAsset_UnlockAbility::FindUnlockDataByTag(FGameplayTag UnlockTag, FUnlockData& OutUnlockData)
{
	for (auto UnlockData : UnlockDatas)
	{
		if (UnlockData.UnlockTag.MatchesTagExact(UnlockTag))
		{
			OutUnlockData = UnlockData;
			return true;
		}
	}
	return false;
}
