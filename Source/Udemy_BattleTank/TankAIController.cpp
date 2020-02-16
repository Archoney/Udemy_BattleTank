#include "TankAIController.h"
#include "Engine/World.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto TankAimingComponent = GetPawn()->GetComponentByClass(UTankAimingComponent::StaticClass());
	check(TankAimingComponent && "ATankAIController - Tank Aiming Controller is null!");
	AimingComponent = Cast<UTankAimingComponent>(TankAimingComponent);
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!PlayerTank)
	{
		PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
	else
	{
		AimingComponent->Update(DeltaSeconds);

		// AI firing
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		AimingComponent->Fire();

		// AI moving
		MoveToActor(PlayerTank, FollowRadiusFromPlayer);
	}
}
