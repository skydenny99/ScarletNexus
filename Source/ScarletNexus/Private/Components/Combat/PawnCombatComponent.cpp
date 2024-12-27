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
