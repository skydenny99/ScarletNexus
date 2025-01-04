// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/KasaneCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BaseDebugHelper.h"
#include "BaseGameplayTags.h"
#include "PsychAbilityHelperLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Character/Character_Kasane.h"
#include "Components/TargetTrackingSpringArmComponent.h"
#include "Components/UI/PlayerUIComponent.h"


void UKasaneCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    // 카사네 히트 로직
    //Debug::Print(GetOwningPawn()->GetActorLabel() + " Hit!!!!! " + HitActor->GetActorLabel(), FColor::Black);

	
	// HitActor가 이미 처리된 적이 있는지 확인
	if (!KasaneHitActorCounts.Contains(HitActor))
	{
		KasaneHitActorCounts.Add(HitActor, 0);
		UPsychAbilityHelperLibrary::ApplyPsychRecoverGameplayEffect(Cast<ACharacter_Kasane>(GetOwningPawn()));
	}

	// 처리 횟수 증가
	KasaneHitActorCounts[HitActor]++;
	
	
	
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;
	if (ACharacter_Kasane* Kasane = Cast<ACharacter_Kasane>(GetOwningPawn()))
	{
		UTargetTrackingSpringArmComponent* TrackingTargetComp = Kasane->GetTargetTrackingComponent();
		if (TrackingTargetComp && TrackingTargetComp->IsTargetTracking() == false)
		{
			TrackingTargetComp->SetCurrentTrackingTarget(HitActor);
			TrackingTargetComp->ToggleTargetTracking();
			Kasane->GetPlayerUIComponent()->OnTargetting.Broadcast(TrackingTargetComp->GetTargetActor());
		}
	}

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), BaseGameplayTags::Shared_Event_Hit_Normal, Data);
	
	// 처리 횟수가 KasaneHitnumber를 초과하면 리턴
	if (KasaneHitActorCounts[HitActor] > KasaneHitnumber)
	{
		//Debug::Print("Kasane Hit Return!");
		return;
	}
}

void UKasaneCombatComponent::OnWeaponPulledFromTargetActor(AActor* InterectedActor)
{
        
}
