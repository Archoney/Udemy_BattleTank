// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankPawn.h"
#include "TankPlayerController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATankPawn* ATankAIController::GetControlledTank() const
{
	static auto controlledTank = Cast<ATankPawn>(GetPawn());
	check(controlledTank && "AIController do not possess any tank!");
	return controlledTank;
}

ATankPawn* ATankAIController::GetPlayerTank() const
{
	static auto playerControlledTank = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController())->GetControlledTank();
	check(playerControlledTank && "Player Controller not found on scene or do not possess a tank!");
	return playerControlledTank;
}
