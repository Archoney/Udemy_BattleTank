// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankPawn.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Custom player controller begin play"));
}

ATankPawn* ATankPlayerController::GetTankPawn() const
{
	return Cast<ATankPawn>(GetPawn());
}