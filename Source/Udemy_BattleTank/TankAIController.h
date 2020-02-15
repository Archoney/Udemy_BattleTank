#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATankPawn;

UCLASS()
class UDEMY_BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

private:
	ATankPawn* ControlledTank;
	ATankPawn* PlayerControlledTank;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float AcceptanceRadius = 1000.0f;
};
