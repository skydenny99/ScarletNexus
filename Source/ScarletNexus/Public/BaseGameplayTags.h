// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "NativeGameplayTags.h"

namespace BaseGameplayTags
{
#pragma region InputTags

	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);

	//Movement
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Dodge);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump);

	//Attack
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Attack_Weapon_Normal);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Attack_Weapon_Special);

	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Attack_Psych_Normal);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Attack_Psych_Special);

	//Targeting (LockOn)
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Targeting_On);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Targeting_Off);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Targeting_Change_Left);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Targeting_Change_Right);

	//Item
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Item_Use);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Item_Change_Left);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Item_Change_Right);

	//SAS
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SAS_First);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SAS_Second);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SAS_Third);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SAS_Fourth);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SAS_Change);

	//TagAttack
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_TagAttack_First);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_TagAttack_Second);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_TagAttack_Third);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_TagAttack_Fourth);

	//ETC
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_AssaultVision);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_BrainCrush);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Revive);


	// History
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_History_Move_Vertical);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_History_Move_Vertical_Forward);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_History_Move_Vertical_Backward);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_History_Move_Horizontal);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_History_Move_Horizontal_Left);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_History_Move_Horizontal_Right);

	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_History_Jump);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_History_Targeting);

#pragma endregion

#pragma region Player

	// Ability - Attack
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Ground_Weapon);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Ground_Psych);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Ground_Charge);

	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Aerial_Weapon);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Aerial_Psych);

	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Backstep);

	// Ability - Move
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Move_Dash);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Move_Dodge);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Move_Jump);

	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_BrainCrush);

	// Ability - JustDodge
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_JustDodge_Weapon);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_JustDodge_Psych);


	// Status
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_SAS_Accel);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_SAS_Elemental_Fire);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_SAS_Elemental_Electric);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_SAS_Stealth);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_SAS_Clone);

	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Move_Run);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Move_Dash);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Move_Dodge_Instant);

	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Move_Aerial);

#pragma endregion

#pragma region Unlock

	//Unlock - Player
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unlock_DoubleJump);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unlock_Aerial_Dash);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unlock_Aerial_DoubleDash);
	//SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unlock_GroundCombo_Fourth);
	//SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unlock_GroundCombo_Fifth);

#pragma endregion


#pragma region Shared

	// Shared - Ability
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Elemental_Fire);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Elemental_Electric);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Elemental_Water);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Elemental_Oil);


	// Shared - Event
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_Hit_Normal);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_Hit_Critical);
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_Hit_KnockDown);

#pragma endregion


#pragma region Fellow Character
	SCARLETNEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fellow_Ability_Attack_Normal);



#pragma endregion
	

	
}