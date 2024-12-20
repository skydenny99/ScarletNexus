// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attribute/EnemyAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "BaseDebugHelper.h"
#include "BaseFunctionLibrary.h"
#include "BaseGameplayTags.h"

UEnemyAttributeSet::UEnemyAttributeSet()
{
	
	InitCurrentHp(1.f);
	InitMaxHp(1.f);
	InitCurrentDownGauge(1.f);
	InitMaxDownGauge(1.f);
	InitCurrentBrainCrushGauge(1.f);
	InitMaxBrainCrushGauge(1.f);
	InitEnemyAttack(1.f);
	InitDamageTaken(1.f);

	Debug::Print(TEXT("Enemy InitAttribute"));
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetCurrentHpAttribute())
	{
		const float NewCurrentHp = FMath::Clamp(GetCurrentHp(), 0.0f, GetMaxHp());
		SetCurrentHp(NewCurrentHp);
	}
	

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float BeforeHp = GetCurrentHp();
		const float BeforeDownGauge = GetCurrentDownGauge();
		const float BeforeBrainCrushGauge = GetCurrentBrainCrushGauge();
		
		const float Damage = GetDamageTaken();

		// HP
		const float NewCurrentHp = FMath::Clamp(BeforeHp - Damage, 0.0f, GetMaxHp());
		SetCurrentHp(NewCurrentHp);
		
		// Down Gauge
		const float NewDownGauge = FMath::Clamp(BeforeDownGauge - Damage/2, 0.0f, GetMaxDownGauge());
		SetCurrentDownGauge(NewDownGauge);
		
		// BrainCrush Gauge
		const float NewBrainCrushGauge = FMath::Clamp(BeforeBrainCrushGauge - Damage/3, 0.0f, GetMaxBrainCrushGauge());
		SetCurrentBrainCrushGauge(NewBrainCrushGauge);
		

		// const FString DebugString = FString::Printf(TEXT("Before Hp: %f, Damage: %f, NewCurrentHp : %f"), BeforeHp, Damage, NewCurrentHp);
		// Debug::Print(DebugString, FColor::Green);


		// Down Process
		if (NewDownGauge <= 0.f)
		{
			UBaseFunctionLibrary::AddPlaygameTagToActor(Data.Target.GetAvatarActor(), BaseGameplayTags::Enemy_State_Down);
			UBaseFunctionLibrary::NativeGetAbilitySystemComponentFromActor(Data.Target.GetAvatarActor())->TryActivateAbilityByTag(BaseGameplayTags::Enemy_Common_Ability_Status_down);

			// 다운상태일시 회복
			if (UBaseFunctionLibrary::NativeActorHasTag(Data.Target.GetAvatarActor(),BaseGameplayTags::Enemy_State_Down))
			{
				SetCurrentDownGauge(GetMaxDownGauge());
				UBaseFunctionLibrary::RemovePlayGameTagFromActor(Data.Target.GetAvatarActor(), BaseGameplayTags::Enemy_State_Down);
			}
			
		}


		// brain Crush
		if (NewBrainCrushGauge <= 0.f)
		{
			UBaseFunctionLibrary::AddPlaygameTagToActor(Data.Target.GetAvatarActor(), BaseGameplayTags::Enemy_State_BCChance);
			UBaseFunctionLibrary::NativeGetAbilitySystemComponentFromActor(Data.Target.GetAvatarActor())->TryActivateAbilityByTag(BaseGameplayTags::Enemy_Common_Ability_Status_BCChance);

			if (UBaseFunctionLibrary::NativeActorHasTag(Data.Target.GetAvatarActor(),BaseGameplayTags::Enemy_State_BCChance))
			{
				SetCurrentBrainCrushGauge(GetMaxBrainCrushGauge());
				UBaseFunctionLibrary::RemovePlayGameTagFromActor(Data.Target.GetAvatarActor(), BaseGameplayTags::Enemy_State_BCChance);				
			}
		}
		
		
	}


}
