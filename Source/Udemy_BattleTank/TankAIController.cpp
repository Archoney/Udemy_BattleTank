#include "TankAIController.h"
#include "TankPawn.h"
#include "Engine/World.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto Pawn = GetPawn();
	check(Pawn && "ATankAIController - pawn is null!");
	auto AITank = Cast<ATankPawn>(Pawn);
	auto TankAimingComponent = AITank->GetComponentByClass(UTankAimingComponent::StaticClass());
	check(TankAimingComponent && "ATankAIController - Tank Aiming Controller is null!");
	AimingComponent = Cast<UTankAimingComponent>(TankAimingComponent);
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!PlayerTank)
	{
		PlayerTank = Cast<ATankPlayerController>(
			GetWorld()->GetFirstPlayerController())->GetPlayerTank();
		ensure(PlayerTank && "ATankAIController - PlayerTank is null!");
	}
	else
	{
		// AI firing
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		AimingComponent->Fire();

		// AI moving
		MoveToActor(PlayerTank, FollowRadiusFromPlayer);
	}
}
