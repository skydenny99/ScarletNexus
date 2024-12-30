// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapon/WeaponBase.h"
#include "Components/BoxComponent.h"
#include "BaseDebugHelper.h"


void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag WeaponTag, AWeaponBase* Weapon,
	bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(WeaponTag), TEXT("%s has already been carried as a weapon"), *WeaponTag.ToString());
	check(Weapon);
	CharacterCarriedWeaponMap.Emplace(WeaponTag, Weapon);


	Weapon->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	Weapon->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);
	
	//장착한 무기로 등록이 되면 현재장착무기를 변경
	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = WeaponTag;
	}
	
	const FString WeaponString = FString::Printf(TEXT("%s has been registerd using the tag: %s"),*Weapon->GetName(), *WeaponTag.ToString());
	Debug::Print(WeaponString);
	
}

void UPawnCombatComponent::RegisterKasaneSpawnedWeapon(FGameplayTag WeaponTag, AWeaponBase* Weapon,
	bool bRegisterAsEquippedWeapon)
{
	// 무기가 6개 이상 등록되지 않도록 제한
	const int32 MaxWeapons = 6;
	if (CharacterCarriedWeaponMap.Num() >= MaxWeapons)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot register more than %d weapons."), MaxWeapons);
		return;
	}

	checkf(!CharacterCarriedWeaponMap.Contains(WeaponTag), TEXT("%s has already been carried as a weapon"), *WeaponTag.ToString());
	check(Weapon);
	CharacterCarriedWeaponMap.Emplace(WeaponTag, Weapon);

	Weapon->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	Weapon->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);

	// 장착한 무기로 등록
	if (bRegisterAsEquippedWeapon)
	{
		if (CurrentEquippedWeaponTags.Num() >= MaxWeapons)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot equip more than %d weapons."), MaxWeapons);
		}
		else
		{
			const FString WeaponString = FString::Printf(TEXT("%s has been registered using the tag: %s"), *Weapon->GetName(), *WeaponTag.ToString());
			Debug::Print(WeaponString);
			CurrentEquippedWeaponTags.AddUnique(WeaponTag);
		}
	}

	// const FString WeaponString = FString::Printf(TEXT("%s has been registered using the tag: %s"), *Weapon->GetName(), *WeaponTag.ToString());
	// Debug::Print(WeaponString);
	
}

AWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag WeaponTag) const
{
	//Map 컨테이너에 WeaponTag의 데이터가 있으면 AWeaponBase 반환
	if (CharacterCarriedWeaponMap.Contains(WeaponTag))
	{
		if (AWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(WeaponTag))
		{
			return *FoundWeapon;
		}
	}
	return nullptr;
}

AWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::ToggleWeaponCollision(bool bUse)
{
	AWeaponBase* Weapon = GetCharacterCurrentEquippedWeapon();
	// check(Weapon);

	if (bUse)
	{
		Weapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		// Debug::Print(Weapon->GetName() + TEXT(" Collision enabled"), FColor::Green);
	}
	else
	{
		Weapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		// Debug::Print(Weapon->GetName() + TEXT(" Collision disabled"), FColor::Red);
		OverlappedActors.Empty();
		
	}


}

AWeaponBase* UPawnCombatComponent::GetWeaponByTag(const FGameplayTag& WeaponTag) const
{
	// CharacterCarriedWeaponMap에서 WeaponTag가 있는지 확인
	if (CharacterCarriedWeaponMap.Contains(WeaponTag))
	{
		// WeaponTag에 연결된 AWeaponBase* 반환
		return CharacterCarriedWeaponMap[WeaponTag];
	}


	// 태그에 해당하는 무기가 없으면 nullptr 반환
	return nullptr;
}


void UPawnCombatComponent::ToggleKasaneWeaponCollision(bool bUse, int32 KasaneHitCount)
{
	//타격 횟수 세팅
	KasaneHitnumber = KasaneHitCount;
	
	// 현재 장착된 모든 무기를 순회
	for (const FGameplayTag& WeaponTag : CurrentEquippedWeaponTags)
	{
		if (AWeaponBase* Weapon = GetWeaponByTag(WeaponTag))
		{
			if (bUse)
			{
				Weapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
				
				// Debug::Print(Weapon->GetName() + TEXT(" Collision enabled"), FColor::Green);
			}
			else
			{
				Weapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				// Debug::Print(Weapon->GetName() + TEXT(" Collision disabled"), FColor::Red);

				// 충돌 비활성화 시 겹쳐진 액터 정보 초기화
				// OverlappedActors.Empty();
				KasaneHitActorCounts.Empty();
				
			}
		}
	}
	
}
