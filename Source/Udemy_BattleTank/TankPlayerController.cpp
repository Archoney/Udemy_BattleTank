// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankPawn.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimAtCrosshair();
}

ATankPawn* ATankPlayerController::GetControlledTank() const
{
	static auto controlledTank = Cast<ATankPawn>(GetPawn());
	check(controlledTank && "PlayerController do not possess any tank!");
	return controlledTank;
}

void ATankPlayerController::AimAtCrosshair()
{
	auto hitLocation = GetSightRayHitLocation();
	if (hitLocation)
	{
		// Aim at hit location
	}
}

TOptional<FVector> ATankPlayerController::GetSightRayHitLocation() const
{
	auto lookDirection = GetLookDirection();
	if (lookDirection)
	{

	}
	return TOptional<FVector>();
}

TOptional<FVector> ATankPlayerController::GetLookDirection() const
{
	if (m_crosshairCanvasPosition)
	{
		int32 viewportSizeX, viewportSizeY;
		GetViewportSize(viewportSizeX, viewportSizeY);

		auto crosshairViewportPosition = FVector2D{
			viewportSizeX * m_crosshairCanvasPosition.GetValue().X,
			viewportSizeX * m_crosshairCanvasPosition.GetValue().Y };

		FVector worldLocation, worldDirection;
		DeprojectScreenPositionToWorld(
			crosshairViewportPosition.X,
			crosshairViewportPosition.Y,
			worldLocation,
			worldDirection
		);

		return worldDirection;
	}
	return TOptional<FVector>();
}

void ATankPlayerController::SetCrosshairPositionOnCanvas(const FVector2D& position)
{
	m_crosshairCanvasPosition.Emplace(position);
}
