// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankPawn.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"

// DEBUG
// #include "DrawDebugHelpers.h"

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
		GetControlledTank()->AimAt(hitLocation.GetValue());
	}
}

TOptional<FVector> ATankPlayerController::GetSightRayHitLocation() const
{
	auto lookDirection = GetLookDirection();
	if (lookDirection)
	{
		return GetLookVectorHitLocation(lookDirection.GetValue());
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
			viewportSizeY * m_crosshairCanvasPosition.GetValue().Y };

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

TOptional<FVector> ATankPlayerController::GetLookVectorHitLocation(const FVector& lookDirection) const
{
	FHitResult hitResult;
	auto lineTraceStart = PlayerCameraManager->GetCameraLocation();
	auto lineTraceLength = 1000000.0f;
	auto lineTraceEnd = lineTraceStart + lookDirection * lineTraceLength;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, lineTraceStart, lineTraceEnd, ECC_Visibility))
	{
		// DEBUG
		// UE_LOG(LogTemp, Warning, TEXT("Object hit: %s"), *hitResult.GetActor()->GetFullName());
		// DrawDebugLine(GetWorld(), lineTraceStart, lineTraceEnd, FColor(1.0f, 0.0f, 0.0f, 1.0f), false, -1.0f, 0, 10.0f);
		return hitResult.Location;
	}

	return TOptional<FVector>();
}

void ATankPlayerController::SetCrosshairPositionOnCanvas(const FVector2D& position)
{
	m_crosshairCanvasPosition.Emplace(position);
}
