// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseFunctionLibrary.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Kismet/KismetMathLibrary.h"

UBaseAbilitySystemComponent* UBaseFunctionLibrary::NativeGetAbilitySystemComponentFromActor(AActor* Actor)
{
	check(Actor);

	return CastChecked<UBaseAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor));
}

void UBaseFunctionLibrary::AddPlaygameTagToActor(AActor* Actor, FGameplayTag Tag)
{
	UBaseAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);
	if (ASC->HasMatchingGameplayTag(Tag) == false)
	{
		ASC->AddLooseGameplayTag(Tag);
	}
}

void UBaseFunctionLibrary::RemovePlayGameTagFromActor(AActor* Actor, FGameplayTag Tag)
{
	UBaseAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);
	if (ASC->HasMatchingGameplayTag(Tag))
	{
		ASC->RemoveLooseGameplayTag(Tag);
	}
}

bool UBaseFunctionLibrary::NativeActorHasTag(AActor* Actor, FGameplayTag Tag)
{
	UBaseAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);

	return ASC->HasMatchingGameplayTag(Tag);
}

bool UBaseFunctionLibrary::NativeActorHasAnyTags(AActor* Actor, FGameplayTagContainer Tags)
{
	UBaseAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);

	return ASC->HasAnyMatchingGameplayTags(Tags);
}

void UBaseFunctionLibrary::BP_HasTag(AActor* Actor, FGameplayTag Tag, EBaseConfirmType& OutType)
{
	OutType = NativeActorHasTag(Actor, Tag) ? EBaseConfirmType::Yes : EBaseConfirmType::No;
}

UPawnCombatComponent* UBaseFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* Actor)
{
	check(Actor);
	if (IPawnCombatInterface* PawnCombatInterFace = Cast<IPawnCombatInterface>(Actor))
	{
		return PawnCombatInterFace->GetPawnCombatComponent();
	}
	return nullptr;
}

UPawnCombatComponent* UBaseFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* Actor,
	EBaseValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(Actor);
	OutValidType = CombatComponent ? EBaseValidType::Valid : EBaseValidType::InValid;

	return CombatComponent;
}

EBaseAIDirectionType UBaseFunctionLibrary::ComputeAIDirection(AActor* Target, AActor* SelfActor,
	float& OutAngleDifference)
{
	// 피격자의 Forward 벡터와 공격자 방향 벡터를 정규화
	const FVector HitForward = SelfActor->GetActorForwardVector();
	const FVector HitToAttackerNormalized = (Target->GetActorLocation() - SelfActor->GetActorLocation()).GetSafeNormal();

	// 내적을 통해 각도 값 구하기
	const float DotResult = FVector::DotProduct(HitForward, HitToAttackerNormalized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	// 외적을 통해 좌우 방향 판단
	const FVector CrossResult = FVector::CrossProduct(HitForward, HitToAttackerNormalized);

	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.f; // 각도를 음수로 변경 (왼쪽 방향)
	}

	// 각도에 따라 방향 결정
	if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
	{
		return EBaseAIDirectionType::Forward; // 정면
	}
	else if (OutAngleDifference > 45.f && OutAngleDifference < 135.f)
	{
		return EBaseAIDirectionType::Right; // 오른쪽
	}
	else if (OutAngleDifference >= -135.f && OutAngleDifference < -45.f)
	{
		return EBaseAIDirectionType::Left; // 왼쪽
	}
	else
	{
		return EBaseAIDirectionType::Backward; // 후면
	}

	// 기본값
	return EBaseAIDirectionType::None;


	
}
