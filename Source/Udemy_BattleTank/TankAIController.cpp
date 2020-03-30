#include "TankAIController.h"
#include "Engine/World.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "TankPawn.h"

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
		auto MoveResult = MoveToActor(PlayerTank, FollowRadiusFromPlayer);

		auto Target = PlayerTank->GetActorLocation() + FVector{ 0.0f, 0.0f, 120.0f };
		AimingComponent->AimAt(Target);

		if (AimingComponent->IsLocked())
			AimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	auto PossessedTank = Cast<ATankPawn>(InPawn);
	if (PossessedTank)
	{
		PossessedTank->TankDestroyed.AddUniqueDynamic(this, &ATankAIController::OnTankDestroyed);
	}
}

void ATankAIController::OnTankDestroyed()
{
	GetPawn()->DetachFromControllerPendingDestroy();
	AimingComponent->OnTankDestroyed();
}
