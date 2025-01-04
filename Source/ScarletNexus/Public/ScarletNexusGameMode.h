// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "BaseType/BaseStructType.h"
#include "GameFramework/GameModeBase.h"
#include "ScarletNexusGameMode.generated.h"


//Player
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPercentValueChanged, float, Percent);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnfloatValueChanged, float, HelathPoint);
//DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnNameHpChanged, FString&, Name, float, HelathPoint);
//DECLARE_DYNAMIC_DELEGATE_OneParam(FOnDebuffChanged, EBaseDebuffType, DebuffType);

//Item
//DECLARE_DYNAMIC_DELEGATE_OneParam(FItemChangeDelegate, FConsumItemInfo, NewItem);
//DECLARE_DYNAMIC_DELEGATE_TwoParams(FItemInitDelegate,const TArray<FConsumItemInfo>&, Array,int32, Index);
//DECLARE_DYNAMIC_DELEGATE_TwoParams(FUpdateAfterDelegate,const TArray<FConsumItemInfo>&, Array,int32, Index);
//DECLARE_DYNAMIC_DELEGATE_ThreeParams(FUpdateBeforeDelegate,const TArray<FConsumItemInfo>&, Array,int32, Index,bool,isLeft);

//Fellow
//DECLARE_DYNAMIC_DELEGATE_TwoParams(FFellowRightInitDelegate,FString, RightName, float, RightHp);
//DECLARE_DYNAMIC_DELEGATE_TwoParams(FFellowLeftInitDelegate,FString, LeftName,float , LeftHp);

//SASBackGround
//DECLARE_DYNAMIC_DELEGATE(FOnKeyDownDelegate);

//SAS
//DECLARE_DYNAMIC_DELEGATE_OneParam(FInitSASSimbolDelegate,const TArray<FSASData>&,NewData);
//DECLARE_DYNAMIC_DELEGATE_TwoParams(FInitGaugeDelegate, FColor,NewColor, float,NewPercent);

//Announcer
//DECLARE_DYNAMIC_DELEGATE_TwoParams(FAnnouncerDelegate, UMaterial* ,NewMaterial, FString, NewText);


/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API AScarletNexusGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;
	
protected:	
	/*UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUD_Class;

	UPROPERTY(BlueprintReadOnly)
	UUserWidget* HUD;*/

	UPROPERTY(BlueprintReadOnly)
	TArray<FSASData> SASData;
	
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	UDataTable* SASDataTable;
	
public:
	/*UFUNCTION()
	virtual void BeginPlay() override;*/
	
	UFUNCTION(BlueprintCallable)
	void BP_BindPercentWithAttributeChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute, FOnPercentValueChanged OnPercentValueChanged);

	UFUNCTION(BlueprintCallable)
	void BP_BindHealthPointWithAttributChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, FOnfloatValueChanged OnFloatValueChanged);

	UFUNCTION(BlueprintImplementableEvent)
	void OnFinalStage();
	/*
	UFUNCTION(BlueprintCallable)
	void BP_BindDebuffWithAttributeChanageDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, FOnDebuffChanged OnDebuffChanged);

	UFUNCTION(BlueprintCallable)
	void BP_BindInitNameHpWithAttributeChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute, FOnNameHpChanged OnNameHpChanged);

	//Item
	UFUNCTION(BlueprintCallable)
	void BP_BindItemChangeWithAttributeChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute, FItemChangeDelegate OnItemChanged);

	UFUNCTION(BlueprintCallable)
	void BP_BindUpdateAfterWithAttributeChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute, FUpdateAfterDelegate OnUpdateAfterItemChanged);

	UFUNCTION(BlueprintCallable)
	void BP_BindUpdateBeforeWithAttributeChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute, FUpdateBeforeDelegate OnUpdateBeforeItemChanged);

	//Fellow
	UFUNCTION(BlueprintCallable)
	void BP_BindFellowRightInitWithAttributeChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute, FFellowRightInitDelegate OnRightInitChanged);

	UFUNCTION(BlueprintCallable)
	void BP_BindFellowLeftInitWithAttributeChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute, FFellowLeftInitDelegate OnLeftInitChanged);

	//SAS BG
	UFUNCTION(BlueprintCallable)
	void BP_BindSASBGKeyDownWithAttributeChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute,  FOnKeyDownDelegate OnKeyDown);
	*/

	//SAS Gauge
	//UFUNCTION(BlueprintCallable)
	//void BP_BindSASTopGaugeWithAttributeChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute, FOnPercentValueChanged OnPercentValueChanged);

	UFUNCTION(BlueprintCallable)
	void InitSASData();
};
