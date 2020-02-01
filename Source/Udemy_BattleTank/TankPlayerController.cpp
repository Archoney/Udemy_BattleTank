// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankPawn.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(GetTankPawn() && "PlayerController do not possess anything!");
}

ATankPawn* ATankPlayerController::GetTankPawn() const
{
	return Cast<ATankPawn>(GetPawn());
}