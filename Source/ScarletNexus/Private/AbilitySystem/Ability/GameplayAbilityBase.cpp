// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GameplayAbilityBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "BaseDebugHelper.h"
#include "BaseGameplayTags.h"
#include "BaseType/BaseEnumType.h"


UBaseAbilitySystemComponent* UGameplayAbilityBase::GetBaseAbilitySystemComponent() const
{
    return Cast<UBaseAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

UPawnCombatComponent* UGameplayAbilityBase::GetPawnCombatComponentFromActorInfo() const
{
    return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

FActiveGameplayEffectHandle UGameplayAbilityBase::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,const FGameplayEffectSpecHandle& SpecHandle)
{
    UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
    check(ASC && SpecHandle.IsValid());
    
    return GetBaseAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, ASC);    
}

FActiveGameplayEffectHandle UGameplayAbilityBase::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor,
    const FGameplayEffectSpecHandle& SpecHandle, EBaseSuccessType& OutSuccessType)
{
    FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, SpecHandle);

    OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EBaseSuccessType::Success : EBaseSuccessType::Failed;

    return ActiveGameplayEffectHandle;
}

FGameplayEffectSpecHandle UGameplayAbilityBase::MakeKasaneDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect,
    const FScalableFloat& DamageFloat)
{
    check(Effect);

    FGameplayEffectContextHandle ContextHandle;
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

    FGameplayEffectSpecHandle SpecHandle = GetBaseAbilitySystemComponent()->MakeOutgoingSpec(
        Effect,
        GetAbilityLevel(),
        ContextHandle
    );
	
    SpecHandle.Data->SetSetByCallerMagnitude(BaseGameplayTags::Shared_SetByCaller_BaseDamage,DamageFloat.GetValueAtLevel(GetAbilityLevel()));
    return SpecHandle;
    
}
