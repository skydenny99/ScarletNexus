// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ExtentionComponent.h"

#include "PawnCombatComponent.generated.h"

class AWeaponBase;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UPawnCombatComponent : public UExtentionComponent
{
	GENERATED_BODY()
	
public:
	// 생성된 무기 등록
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void RegisterSpawnedWeapon(FGameplayTag WeaponTag, AWeaponBase* Weapon, bool bRegisterAsEquippedWeapon = false);

	// 캐릭터가 휴대하는 무기
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	AWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag WeaponTag) const;

	// 캐릭터가 소유한 무기의 태그
	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	FGameplayTag CurrentEquippedWeaponTag;

	//캐릭터가 장착한 무기
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	AWeaponBase* GetCharacterCurrentEquippedWeapon() const;

private:
	//캐릭터 무기 태그 맵
	TMap<FGameplayTag, AWeaponBase*> CharacterCarriedWeaponMap;

	
};
