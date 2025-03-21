
#include "BaseGameplayTags.h"

namespace BaseGameplayTags
{
#pragma region InputTags

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");

	//Movement
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Dodge, "InputTag.Dodge");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_QuickStanding, "InputTag.QuickStanding");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");

	//Attack
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Weapon_Normal, "InputTag.Attack.Weapon.Normal");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Weapon_Special, "InputTag.Attack.Weapon.Special");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Weapon_Jump, "InputTag.Attack.Weapon.Jump");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Psych_Normal, "InputTag.Attack.Psych.Normal");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Psych_Special, "InputTag.Attack.Psych.Special");

	//Targeting (LockOn)
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Targeting_Toggle, "InputTag.Targeting.Toggle");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Targeting_Change, "InputTag.Targeting.Change");

	//Item
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Item_Use, "InputTag.Item.Use");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Item_Change, "InputTag.Item.Change");

	//SAS
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SAS_First, "InputTag.SAS.First");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SAS_Second, "InputTag.SAS.Second");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SAS_Third, "InputTag.SAS.Third");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SAS_Fourth, "InputTag.SAS.Fourth");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SAS_Cancel, "InputTag.SAS.Cancel");
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
	UE_DEFINE_GAMEPLAY_TAG(InputTag_History_Move_Vertical, "InputTag.History.Move.Vertical");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_History_Move_Vertical_Forward, "InputTag.History.Move.Vertical.Forward");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_History_Move_Vertical_Backward, "InputTag.History.Move.Vertical.Backward");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_History_Move_Horizontal, "InputTag.History.Move.Horizontal");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_History_Move_Horizontal_Left, "InputTag.History.Move.Horizontal.Left");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_History_Move_Horizontal_Right, "InputTag.History.Move.Horizontal.Right");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_History_Jump, "InputTag.History.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_History_Targeting, "InputTag.History.Targeting");

#pragma endregion

#pragma region Player

	// Ability - Attack
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Ground_Weapon, "Player.Ability.Attack.Ground.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Ground_Weapon_Fire, "Player.Ability.Attack.Ground.Weapon.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Ground_Psych, "Player.Ability.Attack.Ground.Psych");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Ground_Charge, "Player.Ability.Attack.Ground.Charge");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Ground_Charge_Fire, "Player.Ability.Attack.Ground.Charge.Fire");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Aerial_Weapon, "Player.Ability.Attack.Aerial.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Aerial_Weapon_Fire, "Player.Ability.Attack.Aerial.Weapon.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Aerial_Psych, "Player.Ability.Attack.Aerial.Psych");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Aerial_CutDown, "Player.Ability.Attack.Aerial.CutDown");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Special_Psych, "Player.Ability.Attack.Special.Psych");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Ground_Backstep, "Player.Ability.Attack.Ground.Backstep");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Aerial_Backstep, "Player.Ability.Attack.Aerial.Backstep");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Ground_DashAttack, "Player.Ability.Attack.Ground.DashAttack");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Aerial_DashAttack, "Player.Ability.Attack.Aerial.DashAttack");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Ground_ComboDashAttack, "Player.Ability.Attack.Ground.ComboDashAttack");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Aerial_ComboDashAttack, "Player.Ability.Attack.Aerial.ComboDashAttack");

	
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Ground_Somersault, "Player.Ability.Attack.Ground.Somersault");

	// Ability - Move
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Move_Dash, "Player.Ability.Move.Dash");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Move_Dodge, "Player.Ability.Move.Dodge");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Move_Jump, "Player.Ability.Move.Jump");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_BrainCrush, "Player.Ability.BrainCrush");

	// Ability - JustDodge
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_JustDodge_Ground_Weapon, "Player.Ability.JustDodge.Ground.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_JustDodge_Ground_Psych, "Player.Ability.JustDodge.Ground.Psych");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_JustDodge_Aerial_Weapon, "Player.Ability.JustDodge.Aerial.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_JustDodge_Aerial_Psych, "Player.Ability.JustDodge.Aerial.Psych");

	// Status
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_SAS_Accel, "Player.Status.SAS.Accel");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_SAS_Elemental_Fire, "Player.Status.SAS.Elemental.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_SAS_Elemental_Electric, "Player.Status.SAS.Elemental.Electric");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_SAS_Stealth, "Player.Status.SAS.Stealth");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_SAS_Clone, "Player.Status.SAS.Clone");

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Move_Run, "Player.Status.Move.Run");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Move_Dash, "Player.Status.Move.Dash");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Move_Dodge, "Player.Status.Move.Dodge");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Move_Dodge_Instant_Weapon, "Player.Status.Move.Dodge.Instant.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Move_Dodge_Instant_Psych, "Player.Status.Move.Dodge.Instant.Psych");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_ComboDashAttack, "Player.Status.ComboDashAttack");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Charging, "Player.Status.Charging");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_ChargeReady, "Player.Status.ChargeReady");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Gimmick, "Player.Status.Gimmick");

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Move_Aerial, "Player.Status.Move.Aerial");

	// Cooldown
	UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_Item_Heal, "Player.Cooldown.Item.Heal");
	UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_Item_SAS_Recover, "Player.Cooldown.Item.SAS_Recover");

	// Weapon
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_Wp0, "Player.Weapon.Kasane.Wp0");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_Wp1, "Player.Weapon.Kasane.Wp1");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_Wp2, "Player.Weapon.Kasane.Wp2");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_Wp3, "Player.Weapon.Kasane.Wp3");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_Wp4, "Player.Weapon.Kasane.Wp4");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_Wp5, "Player.Weapon.Kasane.Wp5");

	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_L_Wp0, "Player.Weapon.Kasane.L.Wp0");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_L_Wp1, "Player.Weapon.Kasane.L.Wp1");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_L_Wp2, "Player.Weapon.Kasane.L.Wp2");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_L_Wp3, "Player.Weapon.Kasane.L.Wp3");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_L_Wp4, "Player.Weapon.Kasane.L.Wp4");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_L_Wp5, "Player.Weapon.Kasane.L.Wp5");

	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_R_Wp0, "Player.Weapon.Kasane.R.Wp0");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_R_Wp1, "Player.Weapon.Kasane.R.Wp1");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_R_Wp2, "Player.Weapon.Kasane.R.Wp2");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_R_Wp3, "Player.Weapon.Kasane.R.Wp3");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_R_Wp4, "Player.Weapon.Kasane.R.Wp4");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Kasane_R_Wp5, "Player.Weapon.Kasane.R.Wp5");

#pragma endregion

#pragma region Unlock

	UE_DEFINE_GAMEPLAY_TAG(Unlock_DoubleJump, "Unlock.DoubleJump");
	UE_DEFINE_GAMEPLAY_TAG(Unlock_Aerial_Dash, "Unlock.Aerial.Dash");
	UE_DEFINE_GAMEPLAY_TAG(Unlock_Aerial_DoubleDash, "Unlock.Aerial.DoubleDash");
	UE_DEFINE_GAMEPLAY_TAG(Unlock_GroundCombo_Third, "Unlock.GroundCombo.Third");
	UE_DEFINE_GAMEPLAY_TAG(Unlock_GroundCombo_Fourth, "Unlock.GroundCombo.Fourth");

#pragma endregion


#pragma region Shared

	// Shared - Ability
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Elemental_Fire, "Shared.Ability.Elemental.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Elemental_Electric, "Shared.Ability.Elemental.Electric");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Elemental_Water, "Shared.Ability.Elemental.Water");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Elemental_Oil, "Shared.Ability.Elemental.Oil");

	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_SpawnWeapon, "Shared.Ability.SpawnWeapon");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Dead, "Shared.Ability.Dead");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_BrainCrush, "Shared.Ability.BrainCrush");


	// Shared - Event
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Hit_Normal, "Shared.Event.Hit.Normal");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Hit_Critical, "Shared.Event.Hit.Critical");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Hit_KnockDown, "Shared.Event.Hit.KnockDown");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Combo, "Shared.Event.Combo");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Charge_Cancel, "Shared.Event.Charge.Cancel");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Charge, "Shared.Event.Charge");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Gimmick_CanAttack, "Shared.Event.Gimmick.CanAttack");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Gimmick_CannotAttack, "Shared.Event.Gimmick.CannotAttack");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_BrainCrush, "Shared.Event.BrainCrush");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_BrainCrush_Recover, "Shared.Event.BrainCrush.Recover");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Charge_Confirm, "Shared.Event.Charge.Confirm");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_ThrowProjectile, "Shared.Event.ThrowProjectile");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Grounded, "Shared.Event.Grounded");


	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Normal, "Shared.Event.HitReact.Normal");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Critical, "Shared.Event.HitReact.Critical");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_KnockDown, "Shared.Event.HitReact.KnockDown");
	



	// Shared - State
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_CanAttack, "Shared.Status.CanAttack");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_CanMove, "Shared.Status.CanMove");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Direct, "Shared.Status.Direct");
	UE_DEFINE_GAMEPLAY_TAG(Shared_State_Down, "Shared.State.Down");
	UE_DEFINE_GAMEPLAY_TAG(Shared_State_Dead, "Shared.State.Dead");
	UE_DEFINE_GAMEPLAY_TAG(Shared_State_Invincible, "Shared.State.Invincible");


	// Set By Caller
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BasePower, "Shared.SetByCaller.BasePower");
	

#pragma endregion


#pragma region Fellow
	// Ability
	UE_DEFINE_GAMEPLAY_TAG(Fellow_Ability_Attack_Normal, "Fellow.Ability.Attack.Normal");
	UE_DEFINE_GAMEPLAY_TAG(Fellow_Ability_Attack_Special, "Fellow.Ability.Attack.Special");


	
	UE_DEFINE_GAMEPLAY_TAG(Fellow_Ability_Startup_SpawnWeapon, "Fellow.Ability.Startup.SpawnWeapon");

	
	UE_DEFINE_GAMEPLAY_TAG(Fellow_Ability_Move_Dodge, "Fellow.Ability.Move.Dodge");
	UE_DEFINE_GAMEPLAY_TAG(Fellow_Ability_Move_Wakeup, "Fellow.Ability.Move.Wakeup");



	// State
	UE_DEFINE_GAMEPLAY_TAG(Fellow_State_LockOnTarget, "Fellow.State.LockOnTarget");
	UE_DEFINE_GAMEPLAY_TAG(Fellow_State_PlayerFellow, "Fellow.State.PlayerFellow");
	
	UE_DEFINE_GAMEPLAY_TAG(Fellow_State_EquippingWeapon, "Fellow.State.EquippingWeapon");
	
	UE_DEFINE_GAMEPLAY_TAG(Fellow_State_Attacking, "Fellow.State.Attacking");


	// Weapon
	UE_DEFINE_GAMEPLAY_TAG(Fellow_Weapon_Arashi, "Fellow.Weapon.Arashi");
	UE_DEFINE_GAMEPLAY_TAG(Fellow_Weapon_Hanabi, "Fellow.Weapon.Hanabi");

	

#pragma endregion Fellow

#pragma region Enemy
	// Boss
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Boss_Ability_Attack_WaterBall, "Enemy.Boss.Ability.Attack.WaterBall");
	
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Boss_Ability_Attack_MeleeAttack, "Enemy.Boss.Ability.Attack.MeleeAttack");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Boss_Ability_Attack_Jump, "Enemy.Boss.Ability.Attack.Jump");
	
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Boss_Ability_Move_BackRun, "Enemy.Boss.Ability.Move.BackRun");

	
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Boss_Ability_HitReact_SequenceHit, "Enemy.Boss.Ability.HitReact.SequenceHit");
	
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Boss_Ability_JumpAble, "Enemy.Boss.Ability.JumpAble");

	
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Boss_Weapon_Boss, "Enemy.Boss.Weapon.Boss");


	// Boss State
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Boss_State_SequenceAble, "Enemy.Boss.State.SequenceAble");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Boss_State_2Phase, "Enemy.Boss.State.2Phase");



	// CommonEnemy
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Common_Ability_Attack_Melee, "Enemy.Common.Ability.Attack.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Common_Ability_Attack_Ranged, "Enemy.Common.Ability.Attack.Ranged");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Common_Ability_threat, "Enemy.Common.Ability.threat");

	
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Common_Ability_Status_Dead, "Enemy.Common.Ability.Status.Dead");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Common_Ability_Status_down, "Enemy.Common.Ability.Status.down");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Common_Ability_Status_BCChance, "Enemy.Common.Ability.Status.BCChance");

	
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Common_Ability_Spawn_Core, "Enemy.Common.Ability.Spawn.Core");


	// Weapon
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Common_Weapon_em0400, "Enemy.Common.Weapon.em0400");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Common_Weapon_em0500, "Enemy.Common.Weapon.em0500");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Common_Weapon_em0700, "Enemy.Common.Weapon.em0700");

	//EnemyEvent
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_SpawnProjectile, "Enemy.Event.SpawnProjectile");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_SpawnCore, "Enemy.Event.SpawnCore");
	

	// State
	UE_DEFINE_GAMEPLAY_TAG(Enemy_State_Dead, "Enemy.State.Dead");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_State_Down, "Enemy.State.Down");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_State_BCChance, "Enemy.State.BCChance");


	
		
#pragma endregion

	
}