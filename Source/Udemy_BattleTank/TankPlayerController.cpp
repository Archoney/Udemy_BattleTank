#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto TankAimingComponent = GetPawn()->GetComponentByClass(UTankAimingComponent::StaticClass());
	check(TankAimingComponent && "ATankPlayerController - Tank Aiming Controller is null!");
	AimingComponent = Cast<UTankAimingComponent>(TankAimingComponent);
	AimingComponentReady(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimingComponent->Update(DeltaSeconds);

	auto HitLocation = GetSightRayHitLocation();
	if (HitLocation)
	{
		AimingComponent->AimAt(HitLocation.GetValue());
	}
}

void ATankPlayerController::SetCrosshairPositionOnCanvas(const FVector2D& Position)
{
	CrosshairCanvasPosition.Emplace(Position);
}

TOptional<FVector> ATankPlayerController::GetSightRayHitLocation() const
{
	auto LookDirection = GetLookDirection();
	if (LookDirection)
	{
		return GetLookVectorHitLocation(LookDirection.GetValue());
	}
	return TOptional<FVector>();
}

TOptional<FVector> ATankPlayerController::GetLookDirection() const
{
	if (CrosshairCanvasPosition)
	{
		int32 ViewportSizeX, ViewportSizeY;
		GetViewportSize(ViewportSizeX, ViewportSizeY);

		auto crosshairViewportPosition = FVector2D{
			ViewportSizeX * CrosshairCanvasPosition.GetValue().X,
			ViewportSizeY * CrosshairCanvasPosition.GetValue().Y };

		FVector WorldLocation, WorldDirection;
		DeprojectScreenPositionToWorld(
			crosshairViewportPosition.X,
			crosshairViewportPosition.Y,
			WorldLocation,
			WorldDirection
		);

		return WorldDirection;
	}
	return TOptional<FVector>();
}

TOptional<FVector> ATankPlayerController::GetLookVectorHitLocation(const FVector& LookDirection) const
{
	FHitResult HitResult;
	auto LineTraceStart = PlayerCameraManager->GetCameraLocation();
	auto LineTraceLength = 1000000.0f;
	auto LineTraceEnd = LineTraceStart + LookDirection * LineTraceLength;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStart, LineTraceEnd, ECC_Visibility))
	{
		return HitResult.Location;
	}
	return TOptional<FVector>();
}
