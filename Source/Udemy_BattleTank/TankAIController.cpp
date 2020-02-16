#include "TankAIController.h"
#include "TankPawn.h"
#include "TankPlayerController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = Cast<ATankPawn>(GetPawn());
	check(ControlledTank && "ATankAIController - ControlledTank is null!");
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!PlayerControlledTank)
	{
		PlayerControlledTank = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController())->GetControlledTank();
		check(PlayerControlledTank && "ATankAIController - PlayerControlledTank is null!");
	}

	// AI firing
	ControlledTank->AimAt(PlayerControlledTank->GetActorLocation());
	ControlledTank->Fire();

	// AI moving
	MoveToActor(PlayerControlledTank, AcceptanceRadius);
}
