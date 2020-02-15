#include "TankAIController.h"
#include "TankPawn.h"
#include "TankPlayerController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = Cast<ATankPawn>(GetPawn());
	check(ControlledTank && "AIController do not possess any tank!");
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!PlayerControlledTank)
	{
		PlayerControlledTank = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController())->GetControlledTank();
		check(PlayerControlledTank && "Player Controller not found on scene or do not possess a tank!");
	}

	ControlledTank->AimAt(PlayerControlledTank->GetActorLocation());
	//ControlledTank->Fire();

	MoveToActor(PlayerControlledTank, AcceptanceRadius);
}
