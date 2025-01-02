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

	// 카사네 확장
	UFUNCTION(BlueprintCallable,Category= "Weapon")
	void RegisterKasaneSpawnedWeapon(FGameplayTag WeaponTag, AWeaponBase* Weapon, bool bRegisterAsEquippedWeapon = false);

	
	// 캐릭터가 휴대하는 무기
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	AWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag WeaponTag) const;

	// 캐릭터가 소유한 무기의 태그
	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	FGameplayTag CurrentEquippedWeaponTag;

	//캐릭터가 장착한 무기
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	AWeaponBase* GetCharacterCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ToggleWeaponCollision(bool bUse);


	// 카사네무기 반환용
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	AWeaponBase* GetWeaponByTag(const FGameplayTag& WeaponTag) const;
	
	// 카사네 무기 콜리전 토글
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ToggleKasaneWeaponCollision(bool bUse, int32 KasaneHitCount);

	
	//HitDetection
	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InterectedActor);
	

	// 카사네 무기 배열
	TArray<FGameplayTag> CurrentEquippedWeaponTags;

	// 타격 적중 횟수 
	UPROPERTY(BlueprintReadWrite, Category=	"Combat")
	int32 KasaneHitnumber = 4;

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	TMap<AActor*, int32> KasaneHitActorCounts;
	
private:
	//캐릭터 무기 태그 맵
	TMap<FGameplayTag, AWeaponBase*> CharacterCarriedWeaponMap;
	
protected:
	UPROPERTY(BlueprintReadWrite, Category="Combat")
	TArray<AActor*> OverlappedActors;

	

};




inline void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	// 자식 구현	
}

inline void UPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InterectedActor)
{
	// 자식 구현	
}
