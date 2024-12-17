// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class UBoxComponent;

DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*)

UCLASS()
class SCARLETNEXUS_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

	FOnTargetInteractedDelegate OnWeaponHitTarget;
	FOnTargetInteractedDelegate OnWeaponPulledFromTarget;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* OutLineWeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UBoxComponent* WeaponCollsionBox;

	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
   
	UFUNCTION()
	virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

public:
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollsionBox; }
	
};
