// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/DataAsset_StartupBase.h"
#include "AbilitySystemComponent.h"
#include "BaseDebugHelper.h"

void UDataAsset_StartupBase::GiveStartupAbilities(UAbilitySystemComponent* ASC, int32 Level)
{
	check(ASC);

	for (const auto AbilityClass : StartupAbilities)
	{
		if (AbilityClass == nullptr) continue;
		FGameplayAbilitySpec Spec(AbilityClass);
		Spec.SourceObject = ASC->GetAvatarActor();
		Spec.Level = Level;
		ASC->GiveAbility(Spec);
	}

	if (!StartupGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& BP_Effect : StartupGameplayEffects)
		{
			if (!BP_Effect) continue;

			//BP클래스에서 순수 c++클래스를 추출해서 사용
			UGameplayEffect* EffectCDO = BP_Effect->GetDefaultObject<UGameplayEffect>();
			ASC->ApplyGameplayEffectToSelf(EffectCDO, Level, ASC->MakeEffectContext());
		}
	}
	
}
