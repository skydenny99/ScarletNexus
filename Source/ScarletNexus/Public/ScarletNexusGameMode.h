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
	AScarletNexusGameMode();
	
protected:	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUD_Class;

	UPROPERTY(BlueprintReadOnly)
	UUserWidget* HUD;
	
public:
	UFUNCTION()
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void BP_BindHealthPercentWithAttributeChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute, FOnPercentValueChanged OnPercentValueChanged);

	UFUNCTION(BlueprintCallable)
	void BP_BindHealthPointWithAttributChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, FOnfloatValueChanged OnFloatValueChanged);
	
	/*
	UFUNCTION(BlueprintCallable)
	void BP_BindDebuffWithAttributeChanageDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, FOnDebuffChanged OnDebuffChanged);

	UFUNCTION(BlueprintCallable)
	void BP_BindInitNameHpWithAttributChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute, FOnNameHpChanged OnNameHpChanged);

	//Item
	UFUNCTION(BlueprintCallable)
	void BP_BindItemChangeWithAttributChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute, FItemChangeDelegate OnItemChanged);

	UFUNCTION(BlueprintCallable)
	void BP_BindUpdateAfterWithAttributChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute, FUpdateAfterDelegate OnUpdateAfterItemChanged);

	UFUNCTION(BlueprintCallable)
	void BP_BindUpdateBeforeWithAttributChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute, FUpdateBeforeDelegate OnUpdateBeforeItemChanged);

	//Fellow
	UFUNCTION(BlueprintCallable)
	void BP_BindFellowRightInitWithAttributChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute, FFellowRightInitDelegate OnRightInitChanged);

	UFUNCTION(BlueprintCallable)
	void BP_BindFellowLeftInitWithAttributChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute, FFellowLeftInitDelegate OnLeftInitChanged);

	//SAS BG
	UFUNCTION(BlueprintCallable)
	void BP_BindSASBGKeyDownWithAttributChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute,  FOnKeyDownDelegate OnKeyDown);
	*/




	
};
