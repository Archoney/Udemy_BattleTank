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
	auto ControlledTank = Cast<ATankPawn>(GetPawn());
	check(ControlledTank && "AIController do not possess any tank!");
	return ControlledTank;
}

ATankPawn* ATankAIController::GetPlayerTank() const
{
	auto PlayerControlledTank = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController())->GetControlledTank();
	check(PlayerControlledTank && "Player Controller not found on scene or do not possess a tank!");
	return PlayerControlledTank;
}
