// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter/CommonEnemyCharacter.h"

FVector ACommonEnemyCharacter::GetTargetVector()
{
	FVector TargetVector = (MainBody->GetBoneLocation("Target"));
	return TargetVector;
}
