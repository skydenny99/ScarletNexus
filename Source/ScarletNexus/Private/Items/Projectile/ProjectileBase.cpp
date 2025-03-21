// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Projectile/ProjectileBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "NiagaraComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BaseFunctionLibrary.h"
#include "BaseGameplayTags.h"
#include "BaseDebugHelper.h"


class UTimeControlSubsystem;
// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionObjectType(ECC_GameTraceChannel6);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	BoxComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	BoxComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	BoxComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel7, ECR_Overlap);

	BoxComponent->OnComponentHit.AddUniqueDynamic(this, &AProjectileBase::OnProjectileHit);
	BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AProjectileBase::OnProjectileBeginOverlap);
	
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(GetRootComponent());

	//ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 700.0f;
	ProjectileMovementComponent->MaxSpeed = 800.0f;
	ProjectileMovementComponent->Velocity = FVector(1.0f, 0.0f, 0.0f);
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	//수명
	InitialLifeSpan = 4.0f;
	bCanClonable = false;
	bIsUsed = true;
	
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	if (ProjectileDamagePolicy == EProjectileDamagePolicy::OnBeginOverlap)
	{
		//오버랩인경우 오버랩 Response로 변경
		// CollsionBoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
	
	if (auto TimeSubsystem = GetWorld()->GetSubsystem<UTimeControlSubsystem>())
	{
		TimeSubsystem->TimeDilationDelegate.AddUObject(this, &AProjectileBase::SetCustomTimeDilation);
		SetCustomTimeDilation(TimeSubsystem->GetCurrentTimeDilationReason(), TimeSubsystem->GetCurrentCustomTimeDilation());
	}
}

void AProjectileBase::HandleApplyProjectile(APawn* HitPawn, FGameplayEventData& Payload)
{
	checkf(ProjectileDamageSpecHandle.IsValid(), TEXT("ProjectileDamageSpecHandle must be valid"));
	const bool bWasApplied = UBaseFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(GetInstigator(), HitPawn, ProjectileDamageSpecHandle);

	if (bWasApplied)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitPawn,
			BaseGameplayTags::Shared_Event_HitReact_Critical,
			Payload
		);
	}
}

void AProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// BP에서 구현
	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);

	APawn* HitPawn = Cast<APawn>(OtherActor);

	if (!HitPawn)
	{
		Destroy();
		return;
	}

	// GE Data setting
	FGameplayEventData Data;
	Data.Instigator = this;
	Data.Target = HitPawn;
	
	//Debug::Print(GetName() + TEXT(" Projectile Hit Pawn ") + HitPawn->GetName(), FColor::Black);
	//Debug::Print(GetName() + TEXT(" Projectile Hit Pawn ") + HitPawn->GetName(), FColor::Green);
	

	// Data.Target 무적태그 확인
	
	//Apply projectile Damage ::TODO
	HandleApplyProjectile(HitPawn, Data);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitPawn, BaseGameplayTags::Shared_Event_HitReact_KnockDown, Data);
	
	Destroy();
	
	
}

void AProjectileBase::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//Debug::Print(GetName() + TEXT(" Projectile BeginOverlap "), FColor::White);
}

void AProjectileBase::SetCustomTimeDilation(const ETimeDilationReason& _, float TimeDilation)
{
	CustomTimeDilation = TimeDilation;
}



