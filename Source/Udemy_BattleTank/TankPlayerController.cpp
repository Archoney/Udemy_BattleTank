// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankPawn.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GetControlledTank();
}

ATankPawn* ATankPlayerController::GetControlledTank() const
{
	static auto controlledTank = Cast<ATankPawn>(GetPawn());
	check(controlledTank && "PlayerController do not possess any tank!");
	return controlledTank;
}