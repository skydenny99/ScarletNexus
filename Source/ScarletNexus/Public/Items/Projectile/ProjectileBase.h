// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseType/BaseEnumType.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Actor/PsychokineticThrowableProp.h"

#include "ProjectileBase.generated.h"


class UProjectileMovementComponent;
class UBoxComponent;
class UNiagaraComponent;

UCLASS()
class SCARLETNEXUS_API AProjectileBase : public APsychokineticThrowableProp
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();


	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Projectile")
	UBoxComponent* CollsionBoxComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Projectile")
	UNiagaraComponent* NiagaraComponent;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Projectile")
	EProjectileDamagePolicy ProjectileDamagePolicy = EProjectileDamagePolicy::OnHit;
	
	//스폰시 노출가능하도록 메크로에서 ExposeOnSpawn사용
	UPROPERTY(BlueprintReadOnly, Category="Projectile", meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle ProjectileDamageSpecHandle;


	UFUNCTION()
	void HandleApplyProjectile(APawn* HitPawn, FGameplayEventData& Payload);

	
	UFUNCTION()
	virtual void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	UFUNCTION()
	virtual void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Spawn Projectile Hit FX"))
	void BP_OnSpawnProjectileHitFX(const FVector& HitLocation);

	
};
