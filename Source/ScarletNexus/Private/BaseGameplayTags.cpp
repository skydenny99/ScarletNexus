
#include "BaseGameplayTags.h"

namespace BaseGameplayTags
{
#pragma region InputTags

	//Movement
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move_Forward, "InputTag.Move.Forward");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move_Backward, "InputTag.Move.Backward");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move_Left, "InputTag.Move.Left");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move_Right, "InputTag.Move.Right");
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Dodge, "InputTag.Dodge");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");

	//Attack
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Weapon_Normal, "InputTag.Attack.Weapon.Normal");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Weapon_Special, "InputTag.Attack.Weapon.Special");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Psych_Normal, "InputTag.Attack.Psych.Normal");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Psych_Special, "InputTag.Attack.Psych.Special");

	//Targeting (LockOn)
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Targeting_On, "InputTag.Targeting.On");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Targeting_Off, "InputTag.Targeting.Off");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Targeting_Change_Left, "InputTag.Targeting.Change.Left");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Targeting_Change_Right, "InputTag.Targeting.Change.Right");

	//Item
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Item_Use, "InputTag.Item.Use");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Item_Change_Left, "InputTag.Item.Change.Left");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Item_Change_Right, "InputTag.Item.Change.Right");

	//SAS
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SAS_First, "InputTag.SAS.First");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SAS_Second, "InputTag.SAS.Second");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SAS_Third, "InputTag.SAS.Third");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SAS_Fourth, "InputTag.SAS.Fourth");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SAS_Change, "InputTag.SAS.Change");

	//TagAttack
	UE_DEFINE_GAMEPLAY_TAG(InputTag_TagAttack_First, "InputTag.TagAttack.First");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_TagAttack_Second, "InputTag.TagAttack.Second");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_TagAttack_Third, "InputTag.TagAttack.Third");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_TagAttack_Fourth, "InputTag.TagAttack.Fourth");

	//ETC
	UE_DEFINE_GAMEPLAY_TAG(InputTag_AssaultVision, "InputTag.AssaultVision");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_BrainCrush, "InputTag.BrainCrush");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Revive, "InputTag.Revive");


	// History
	UE_DEFINE_GAMEPLAY_TAG(InputTag_History_Move_Forward, "InputTag.History.Move.Forward");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_History_Move_Backward, "InputTag.History.Move.Backward");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_History_Move_Left, "InputTag.History.Move.Left");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_History_Move_Right, "InputTag.History.Move.Right");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_History_Jump, "InputTag.History.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_History_Targeting, "InputTag.History.Targeting");

#pragma endregion

#pragma region Player

	// Ability - Attack
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Ground_Weapon, "Player.Ability.Attack.Ground.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Ground_Psych, "Player.Ability.Attack.Ground.Psych");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Ground_Charge, "Player.Ability.Attack.Ground.Charge");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Aerial_Weapon, "Player.Ability.Attack.Aerial.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Aerial_Psych, "Player.Ability.Attack.Aerial.Psych");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Backstep, "Player.Ability.Attack.Backstep");

	// Ability - Move
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Move_Dash, "Player.Ability.Move.Dash");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Move_Dodge, "Player.Ability.Move.Dodge");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Move_Jump, "Player.Ability.Move.Jump");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_BrainCrush, "Player.Ability.BrainCrush");

	// Ability - JustDodge
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_JustDodge_Weapon, "Player.Ability.JustDodge.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_JustDodge_Psych, "Player.Ability.JustDodge.Psych");

	// Status
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_SAS_Accel, "Player.Status.SAS.Accel");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_SAS_Elemental_Fire, "Player.Status.SAS.Elemental.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_SAS_Elemental_Electric, "Player.Status.SAS.Elemental.Electric");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_SAS_Stealth, "Player.Status.SAS.Stealth");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_SAS_Clone, "Player.Status.SAS.Clone");

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Move_Run, "Player.Status.Move.Run");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Move_Dash, "Player.Status.Move.Dash");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Move_Dodge_Instant, "Player.Status.Move.Dodge.Instant");

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Move_Aerial, "Player.Status.Move.Aerial");

#pragma endregion



#pragma region Shared

	// Shared - Ability
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Elemental_Fire, "Shared.Ability.Elemental.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Elemental_Electric, "Shared.Ability.Elemental.Electric");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Elemental_Water, "Shared.Ability.Elemental.Water");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Elemental_Oil, "Shared.Ability.Elemental.Oil");


	// Shared - Event
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Hit_Normal, "Shared.Event.Hit.Normal");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Hit_Critical, "Shared.Event.Hit.Critical");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Hit_KnockDown, "Shared.Event.Hit.KnockDown");

#pragma endregion
}