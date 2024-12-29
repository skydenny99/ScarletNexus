// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/KasaneCombatComponent.h"
#include "BaseDebugHelper.h"


void UKasaneCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    // 카사네 히트 로직
    Debug::Print(GetOwningPawn()->GetActorLabel() + " Hit " + HitActor->GetActorLabel(), FColor::Black);
    
	// HitActor가 이미 처리된 적이 있는지 확인
	if (!KasaneHitActorCounts.Contains(HitActor))
	{
		KasaneHitActorCounts.Add(HitActor, 0);
	}

	// 처리 횟수 증가
	KasaneHitActorCounts[HitActor]++;

	// 처리 횟수가 KasaneHitnumber를 초과하면 리턴
	if (KasaneHitActorCounts[HitActor] > KasaneHitnumber)
	{
		return;
	}
	

    
}

void UKasaneCombatComponent::OnWeaponPulledFromTargetActor(AActor* InterectedActor)
{
        
}
