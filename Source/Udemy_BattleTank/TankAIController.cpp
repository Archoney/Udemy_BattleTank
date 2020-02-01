// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankPawn.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	check(GetTankPawn() && "AIController do not possess anything!");
}

ATankPawn* ATankAIController::GetTankPawn() const
{
	return Cast<ATankPawn>(GetPawn());
}