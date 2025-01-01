// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "Interfaces/PawnUIInterface.h"
#include "PlayerUIComponent.generated.h"

//PlayerBG
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInitplayerDelegate,const FString&,NewName,const float, MaxHp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeHpDelegate,float,NewHealthPoint);
//Item
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemChangeDelegate, FConsumItemInfo, NewItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemInitDelegate,const TArray<FConsumItemInfo>&, Array,int32, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateAfterDelegate,const TArray<FConsumItemInfo>&, Array,int32, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FUpdateBeforDelegate,const TArray<FConsumItemInfo>&, Array,int32, Index,bool,isLeft);
//Fellow
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FFellowInitDelegate,FString,LeftName,float,LeftHp,FString,RightName, float ,RightHp);
//SASBackGround
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKeyDownDelegate);
//SAS
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInitSASSimbolDelegate,const TArray<FSASData>&,NewData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInitGaugeDelegate, FColor,NewColor, float,NewPercent);
//Announcer
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAnnouncerDelegate, UMaterial* ,NewMaterial, FString, NewText);

//Targetting LockOn
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargettingDelegate,AActor*, NewActor);

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UPlayerUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnPsychPercentChanged;

	//PlayerBG
	UPROPERTY(BlueprintAssignable)
	FInitplayerDelegate OnInitPlayer;

	UPROPERTY(BlueprintAssignable)
	FChangeHpDelegate OnPlayerHpChanged;
	
	//Item
	UPROPERTY(BlueprintAssignable)
	FItemChangeDelegate OnCurrentItemChanged;

	UPROPERTY(BlueprintAssignable)
	FItemInitDelegate OnItemInit;

	UPROPERTY(BlueprintAssignable)
	FUpdateAfterDelegate OnUpdateAfter;

	UPROPERTY(BlueprintAssignable)
	FUpdateBeforDelegate OnUpdateBefore;

	//Fellow
	UPROPERTY(BlueprintAssignable)
	FFellowInitDelegate OnFellowInit;

	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnUpdateFellowLeftHpPercent;

	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnUpdateFellowRightHpPercent;
	
	UPROPERTY(BlueprintAssignable)
	FChangeHpDelegate OnUpdateFellowLeftHp;

	UPROPERTY(BlueprintAssignable)
	FChangeHpDelegate OnUpdateFellowRightHp;
	
	//SASBackGround
	UPROPERTY(BlueprintAssignable)
	FOnKeyDownDelegate OnCtrlKeyDown;
	
	UPROPERTY(BlueprintAssignable)
	FOnKeyDownDelegate OnAltKeyDown;

	UPROPERTY(BlueprintAssignable)
	FOnKeyDownDelegate OnXKeyDown;

	//SAS
	UPROPERTY(BlueprintAssignable)
	FInitSASSimbolDelegate OnInitSASSimbol;

	UPROPERTY(BlueprintAssignable)
	FInitGaugeDelegate OnInitTopGauge;

	UPROPERTY(BlueprintAssignable)
	FInitGaugeDelegate OnInitLeftGauge;

	UPROPERTY(BlueprintAssignable)
	FInitGaugeDelegate OnInitRightGauge;

	UPROPERTY(BlueprintAssignable)
	FInitGaugeDelegate OnInitBottomGauge;

	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnUpdateSASTopGauge;

	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnUpdateSASLeftGauge;

	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnUpdateSASRightGauge;

	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnUpdateSASBottomGauge;

	//Announcer
	UPROPERTY(BlueprintAssignable)
	FAnnouncerDelegate OnUpdateAnnounce;

	//Lock ON
	UPROPERTY(BlueprintAssignable)
	FTargettingDelegate OnTargetting;

	//InterectProp
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnInterectPercentChanged;
};
