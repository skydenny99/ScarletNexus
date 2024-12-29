// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_SASAbilityBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BaseDebugHelper.h"
#include "BaseFunctionLibrary.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "Character/Character_Kasane.h"

FGameplayAttribute UGA_SASAbilityBase::GetCurrentAttribute() const
{
	if (MaxGaugeAttribute == UPlayerAttributeSet::GetMaxAccelGaugeAttribute())
		return UPlayerAttributeSet::GetCurrentAccelGaugeAttribute();
	
	if (MaxGaugeAttribute == UPlayerAttributeSet::GetMaxCloneGaugeAttribute())
		return UPlayerAttributeSet::GetCurrentCloneGaugeAttribute();
	
	if (MaxGaugeAttribute == UPlayerAttributeSet::GetMaxFireGaugeAttribute())
		return UPlayerAttributeSet::GetCurrentFireGaugeAttribute();
	
	if (MaxGaugeAttribute == UPlayerAttributeSet::GetMaxStealthGaugeAttribute())
		return UPlayerAttributeSet::GetCurrentStealthGaugeAttribute();
	
	Debug::Print("UGA_SASAbilityBase::GetAttribute(): Unknown Attribute", FColor::Red);
	return UPlayerAttributeSet::GetCurrentAccelGaugeAttribute();
}

void UGA_SASAbilityBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	Kasane = Cast<ACharacter_Kasane>(ActorInfo->AvatarActor);
	check(Kasane);
	InitOnGiveAbility();
	OnGameplayAbilityCancelled.AddUObject(this, &UGA_SASAbilityBase::ReduceSASGauge);

}

bool UGA_SASAbilityBase::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	bool IsCurrentFound = false;
	float CurrentValue = UAbilitySystemBlueprintLibrary::GetFloatAttribute(Kasane, GetCurrentAttribute(), IsCurrentFound);
	bool IsMaxFound = false;
	float MaxValue = UAbilitySystemBlueprintLibrary::GetFloatAttribute(Kasane, MaxGaugeAttribute, IsMaxFound);

	if (IsCurrentFound == false || IsMaxFound == false) return false;
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return (CurrentValue / MaxValue) >= AllowActivateGaugeRate;
	}
	return false;
}

void UGA_SASAbilityBase::PreActivate(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                     FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
	Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);
	UBaseFunctionLibrary::AddPlaygameTagToActor(Kasane, AbilityTags.First());
}

void UGA_SASAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	OnGameplayAbilityEnded.AddUObject(this, &UGA_SASAbilityBase::OnEndAbility);
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGA_SASAbilityBase::OnEndAbility(UGameplayAbility* Ability)
{
	UBaseFunctionLibrary::RemovePlayGameTagFromActor(Kasane, AbilityTags.First());
}

void UGA_SASAbilityBase::ReduceSASGauge()
{
	// cancel 시에 일정량의 게이지 차감
	bool IsFound = false;
	float AttributeValue = UAbilitySystemBlueprintLibrary::GetFloatAttribute(Kasane, MaxGaugeAttribute, IsFound);
	if (IsFound == false) return;
	GE_ReduceByCancel = NewObject<UGameplayEffect>(GetTransientPackage(), TEXT("ReduceByCancel"));
	GE_ReduceByCancel->DurationPolicy = EGameplayEffectDurationType::Instant;
	
	int32 Idx = GE_ReduceByCancel->Modifiers.Num();
	GE_ReduceByCancel->Modifiers.SetNum(Idx + 1);
	
	FGameplayModifierInfo& InfoReduce = GE_ReduceByCancel->Modifiers[Idx];
	InfoReduce.ModifierMagnitude = FScalableFloat(-AttributeValue * ReduceGaugeRateOnCancel);
	InfoReduce.ModifierOp = EGameplayModOp::Additive;
	InfoReduce.Attribute = GetCurrentAttribute();
	GetBaseAbilitySystemComponent()->ApplyGameplayEffectToSelf(GE_ReduceByCancel, 1.f, GetBaseAbilitySystemComponent()->MakeEffectContext());
}
