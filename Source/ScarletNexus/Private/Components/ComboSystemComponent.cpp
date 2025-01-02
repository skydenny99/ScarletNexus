// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ComboSystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BaseDebugHelper.h"
#include "Character/Character_Kasane.h"
#include "BaseFunctionLibrary.h"
#include "BaseGameplayTags.h"
#include "PsychAbilityHelperLibrary.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Character/EnemyCharacter/BaseEnemyCharacter.h"
#include "DataAsset/DataAsset_AttackAbility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/Projectile/ProjectileBase.h"

// Sets default values for this component's properties
UComboSystemComponent::UComboSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UComboSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	if (Kasane)
	{
		Kasane->MovementModeChangedDelegate.AddDynamic(this, &UComboSystemComponent::OnMovementModeChange);
	}
}


void UComboSystemComponent::InitReferences(ACharacter_Kasane* InKasane, USphereComponent* InJustDodgeBoundary)
{
	Kasane = InKasane;
	if (Kasane)
	{
		BaseAbilitySystemComponent = Kasane->GetBaseAbilitySystemComponent();
		JustDodgeBoundary = InJustDodgeBoundary;
	}
}

void UComboSystemComponent::GrantAttackAbilites(UAbilitySystemComponent* ASC, int32 Level)
{
	check(AbilityAsset);
	for (auto AbilityClass : AbilityAsset->AttackAbilityList)
	{
		if (AbilityClass == nullptr) continue;
		FGameplayAbilitySpec Spec(AbilityClass);
		Spec.SourceObject = ASC->GetAvatarActor();
		Spec.Level = Level;
		ASC->GiveAbility(Spec);
		AbilitySpecs.Add(Spec.Ability->AbilityTags.First(), Spec);
		Debug::Print(FString::Printf(TEXT("%s Ability Granted"), *Spec.Ability->AbilityTags.First().ToString()), FColor::Green);
	}
	UBaseFunctionLibrary::AddPlaygameTagToActor(Kasane, BaseGameplayTags::Shared_Status_CanAttack);
}

bool UComboSystemComponent::TryActivateAbilityByInputTag(FGameplayTag tag)
{
	FGameplayTag AbilityTag = FGameplayTag();
	UCharacterMovementComponent* Movement = Kasane->GetCharacterMovement();
	if (tag.MatchesTagExact(BaseGameplayTags::InputTag_Attack_Weapon_Normal))
	{
		if (UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Player_Status_Move_Dodge_Instant_Weapon))
		{
			AbilityTag = Movement->IsWalking() ? BaseGameplayTags::Player_Ability_JustDodge_Ground_Weapon
			: BaseGameplayTags::Player_Ability_JustDodge_Aerial_Weapon;
			goto Execute;
		}
		
		if (UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Player_Status_ComboDashAttack))
		{
			AbilityTag = Movement->IsWalking() ? BaseGameplayTags::Player_Ability_Attack_Ground_ComboDashAttack
			: BaseGameplayTags::Player_Ability_Attack_Aerial_ComboDashAttack;
			goto Execute;
		}

		if (UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Player_Status_Move_Dodge))
		{
			AbilityTag = Movement->IsWalking() ? BaseGameplayTags::Player_Ability_Attack_Ground_DashAttack
			: BaseGameplayTags::Player_Ability_Attack_Aerial_DashAttack;
			goto Execute;
		}


		if (UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Player_Status_SAS_Elemental_Fire))
		{
			AbilityTag = Movement->IsWalking() ? BaseGameplayTags::Player_Ability_Attack_Ground_Weapon_Fire
			: BaseGameplayTags::Player_Ability_Attack_Aerial_Weapon_Fire;
		}
		else
		{
			AbilityTag = Movement->IsWalking() ? BaseGameplayTags::Player_Ability_Attack_Ground_Weapon
			: BaseGameplayTags::Player_Ability_Attack_Aerial_Weapon;
		}
		
	}
	else if (tag.MatchesTagExact(BaseGameplayTags::InputTag_Attack_Weapon_Special))
	{
		if (ActionElapsedTime > ChargeAttackThreshold)
		{
			if (Movement->IsWalking())
			{
				AbilityTag = UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Player_Status_SAS_Elemental_Fire) ?
					BaseGameplayTags::Player_Ability_Attack_Ground_Charge_Fire : BaseGameplayTags::Player_Ability_Attack_Ground_Charge;
			}
			else
			{
				AbilityTag = BaseGameplayTags::Player_Ability_Attack_Aerial_CutDown;
			}
		}
	}
	else if (tag.MatchesTagExact(BaseGameplayTags::InputTag_Attack_Psych_Normal))
	{
		if (UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Player_Status_Move_Dodge_Instant_Psych))
		{
			AbilityTag = Movement->IsWalking() ? BaseGameplayTags::Player_Ability_JustDodge_Ground_Psych
			: BaseGameplayTags::Player_Ability_JustDodge_Aerial_Psych;
			goto Execute;
		}

		AbilityTag = Movement->IsWalking() ? BaseGameplayTags::Player_Ability_Attack_Ground_Psych
		: BaseGameplayTags::Player_Ability_Attack_Aerial_Psych;
	}
	else if (tag.MatchesTagExact(BaseGameplayTags::InputTag_Attack_Psych_Special))
	{
		AbilityTag = BaseGameplayTags::Player_Ability_Attack_Special_Psych;
	}

	
	Execute:
	
	if (AbilityTag.IsValid() == false || AbilitySpecs.Contains(AbilityTag) == false)
	{
		Debug::Print("Triggered: Ability not found", FColor::Red);
		return false;
	}
	if (BaseAbilitySystemComponent->TryActivateAbility(AbilitySpecs[AbilityTag].Handle))
	{
		LastActivatedGameplayTag = AbilityTag;
		return true;
	}
	
	Debug::Print("Triggered: Ability try failed", FColor::Red);
	return false;
}

void UComboSystemComponent::TryActivateChargeAbility()
{
	FGameplayEventData EventData;
	EventData.Instigator = Kasane;
	EventData.InstigatorTags.AddTag(ActionElapsedTime >= ChargeCompletionTime ? BaseGameplayTags::Shared_Event_Charge_Confirm : BaseGameplayTags::Shared_Event_Charge_Cancel);
	
	Debug::Print(FString::Printf(TEXT("Character Target Name: %s"), *Kasane->GetActorLabel()));
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Kasane, BaseGameplayTags::Shared_Event_Charge, EventData);

	bIsCharging = false;
	UBaseFunctionLibrary::RemovePlayGameTagFromActor(Kasane, BaseGameplayTags::Player_Status_Charging);
	bChargeAbilityAlreadyTriggered = true;
	ActionElapsedTime = 0.f;
}

bool UComboSystemComponent::TryCancelAttackAbility()
{
	if (LastActivatedGameplayTag.IsValid() == false || bIsCharging) return false;
	Debug::Print(FString::Printf(TEXT("Cancel Ability : %s"), *LastActivatedGameplayTag.ToString()), FColor::Red);
	BaseAbilitySystemComponent->CancelAbilityHandle(AbilitySpecs[LastActivatedGameplayTag].Handle);
	LastActivatedGameplayTag = FGameplayTag();
	return true;
}

void UComboSystemComponent::UpdateInfoByUnlock()
{
	if (UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Unlock_GroundCombo_Third))
	{
		WeaponGroundCombo.MaxComboCount = 3;
	}

	if (UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Unlock_GroundCombo_Fourth))
	{
		WeaponGroundCombo.MaxComboCount = 4;
	}
}

void UComboSystemComponent::OnMovementModeChange(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	// Reset All Combo;
	Debug::Print("Reset Weapon Combo Count");
	ResetGroundCombo();
	ResetAerialCombo();
	StopPsychComboTimer();
}


void UComboSystemComponent::ProcessInputAction(FGameplayTag InputTag, ETriggerEvent TriggerEvent, const FInputActionInstance& Instance)
{
	switch (TriggerEvent)
	{
	case ETriggerEvent::Triggered:
		if (bIsCharging)
		{
			if (UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Player_Status_Charging))
			{
				ActionElapsedTime = Instance.GetElapsedTime() - StartActionElapsedTime;
				
				//Debug::Print(FString::Printf(TEXT("Charging %f %f %f"),StartActionElapsedTime, ActionElapsedTime, ChargeCompletionTime), FColor::Blue);
			}
			else
			{
				ActionElapsedTime = 0.f;
				StartActionElapsedTime = Instance.GetElapsedTime();
			}
			if (bIsAutoCompletion && ActionElapsedTime > ChargeCompletionTime)
			{
				TryActivateChargeAbility();
				LastChargeAbilityInputTag = InputTag;
			}
		}
		else
		{
			ActionElapsedTime = Instance.GetElapsedTime();
			if (LastChargeAbilityInputTag.MatchesTagExact(InputTag)) return;
			if (TryActivateAbilityByInputTag(InputTag))
			{
				LastChargeAbilityInputTag = InputTag;
			}
		}
		break;
	case ETriggerEvent::Completed:
		if (LastChargeAbilityInputTag.IsValid())
		{
			if (LastChargeAbilityInputTag.MatchesTagExact(InputTag))
			{
				LastChargeAbilityInputTag = FGameplayTag();
			}
			else
			{
				return;
			}
		}
		if (bIsCharging)
		{
				TryActivateChargeAbility();
		}
		else
		{
			FGameplayTag AbilityTag = FGameplayTag();
			if (Kasane->GetCharacterMovement()->IsWalking() && InputTag == BaseGameplayTags::InputTag_Attack_Weapon_Jump)
			{
				UBaseFunctionLibrary::AddPlaygameTagToActor(Kasane, BaseGameplayTags::Shared_Status_CanAttack);
				AbilityTag = BaseGameplayTags::Player_Ability_Attack_Ground_Somersault;
			}
			else if (InputTag == BaseGameplayTags::InputTag_Attack_Weapon_Special)
			{
				AbilityTag =
					Kasane->GetCharacterMovement()->IsWalking() ?
						BaseGameplayTags::Player_Ability_Attack_Ground_Backstep : BaseGameplayTags::Player_Ability_Attack_Aerial_Backstep;
			}
			
			if (AbilityTag.IsValid() == false || AbilitySpecs.Contains(AbilityTag) == false)
			{
				Debug::Print(FString::Printf(TEXT("Completed: Ability not found - %s"), *InputTag.ToString()), FColor::Red);
				return;
			}
			if (BaseAbilitySystemComponent->TryActivateAbility(AbilitySpecs[AbilityTag].Handle))
			{
				LastActivatedGameplayTag = AbilityTag;
				Debug::Print(FString::Printf(TEXT("Ability %s"), *LastActivatedGameplayTag.ToString()), FColor::Red);
			}
			else
			{
				Debug::Print("Completed: Ability try failed", FColor::Red);
			}
		}
			
		break;
	default:
		break;
	}
}

bool UComboSystemComponent::CheckJustDodge() // 최적화 필요
{
	const float GlobalTimeDilation = .1f;
	if (JustDodgeBoundary == nullptr) return false;

	TSet<AActor*> OverlappedActors;

	JustDodgeBoundary->GetOverlappingActors(OverlappedActors, AProjectileBase::StaticClass()); // BaseProjectile::StaticClass();
	if (OverlappedActors.IsEmpty() == false)
	{
		Debug::Print("Found Projectile");
		AActor* NearestProjectile = nullptr;
		float MinDist = std::numeric_limits<float>::infinity();
		const FVector OwnerLocation = GetOwner()->GetActorLocation();
		for (const auto OverlappedActor : OverlappedActors)
		{
			if (OverlappedActor == GetOwner()) continue;
			float TempDist = FVector::DistSquared(OverlappedActor->GetActorLocation(), OwnerLocation);
			if (TempDist < MinDist)
			{
				NearestProjectile = OverlappedActor;
				MinDist = TempDist;
			}
		}

		if (NearestProjectile != nullptr)
		{
			UPsychAbilityHelperLibrary::NativeOverrideThrowablePsychObject(Kasane, NearestProjectile);
			UBaseFunctionLibrary::AddPlaygameTagToActor(Kasane, BaseGameplayTags::Player_Status_Move_Dodge_Instant_Psych);
			UGameplayStatics::SetGlobalTimeDilation(Kasane, GlobalTimeDilation);
			Debug::Print(FString::Printf(TEXT("Set Nearest Projectile: %s"), *NearestProjectile->GetActorLabel()));
			return true;
		}
	}
	
	JustDodgeBoundary->GetOverlappingActors(OverlappedActors, ABaseEnemyCharacter::StaticClass());
	if (OverlappedActors.IsEmpty()) return false;
	for (auto OverlappedActor : OverlappedActors)
	{
		if (OverlappedActor == GetOwner()) continue;
		Debug::Print("Found EnemyAttack");
		if (UBaseFunctionLibrary::NativeActorHasTag(OverlappedActor, BaseGameplayTags::Shared_Status_CanAttack))
		{
			UBaseFunctionLibrary::AddPlaygameTagToActor(Kasane, BaseGameplayTags::Player_Status_Move_Dodge_Instant_Weapon);
			UGameplayStatics::SetGlobalTimeDilation(Kasane, GlobalTimeDilation); // 저스트 회피 성공 시 느려짐
			return true;
		}
	}
	return false;
}


void UComboSystemComponent::IncreaseCombo(FComboCounter& ComboCounter)
{
	ComboCounter.CurrentComboCount = (ComboCounter.CurrentComboCount + 1) % ComboCounter.MaxComboCount;
}

void UComboSystemComponent::ResetGroundCombo()
{
	WeaponGroundCombo.CurrentComboCount = 0;
	PsychGroundCombo.CurrentComboCount = 0;
	BackstepGroundCombo.CurrentComboCount = 0;
}

void UComboSystemComponent::ResetAerialCombo()
{
	WeaponAerialCombo.CurrentComboCount = 0;
	PsychAerialCombo.CurrentComboCount = 0;
	BackstepAerialCombo.CurrentComboCount = 0;
}

void UComboSystemComponent::ResetWeaponCombo()
{
	WeaponGroundCombo.CurrentComboCount = 0;
	WeaponAerialCombo.CurrentComboCount = 0;
}

void UComboSystemComponent::ResetBackstep()
{
	BackstepGroundCombo.CurrentComboCount = 0;
	BackstepAerialCombo.CurrentComboCount = 0;
}

void UComboSystemComponent::StartPsychComboTimer()
{
	bIsPsychComboAttacking = true;
	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([this]()
	{
		if (this)
		{
			PsychGroundCombo.CurrentComboCount = 0;
			bIsPsychComboAttacking = false;
			Debug::Print("ResetPsychCombo");
		}
	});
	GetWorld()->GetTimerManager().SetTimer(PsychComboResetTimerHandle, timerDelegate, PsychComboResetTime, false);
}

void UComboSystemComponent::ClearPsychComboTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(PsychComboResetTimerHandle);
}

void UComboSystemComponent::StopPsychComboTimer()
{
	PsychGroundCombo.CurrentComboCount = 0;
	PsychAerialCombo.CurrentComboCount = 0;
	bIsPsychComboAttacking = false;
	ClearPsychComboTimer();
}

void UComboSystemComponent::StartComboDashAttackTimer()
{
	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([this]()
	{
		if (this)
		{
			if (Kasane)
			{
				UBaseFunctionLibrary::RemovePlayGameTagFromActor(Kasane, BaseGameplayTags::Player_Status_ComboDashAttack);
			}
		}
	});
	UBaseFunctionLibrary::AddPlaygameTagToActor(Kasane, BaseGameplayTags::Player_Status_ComboDashAttack);
	GetWorld()->GetTimerManager().SetTimer(ComboDashAttackTimerHandle, timerDelegate, ComboDashResetTime, false);
}

