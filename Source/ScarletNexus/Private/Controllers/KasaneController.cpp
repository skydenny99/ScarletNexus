// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/KasaneController.h"

AKasaneController::AKasaneController()
{
	HeroTeamId = FGenericTeamId(1);
}

FGenericTeamId AKasaneController::GetGenericTeamId() const
{
	return HeroTeamId;
}
