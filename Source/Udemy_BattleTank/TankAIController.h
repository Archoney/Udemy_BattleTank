#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATankPawn;
class UTankAimingComponent;

UCLASS()
class UDEMY_BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float FollowRadiusFromPlayer = 8000.0f;

private:
	UTankAimingComponent* AimingComponent{ nullptr };
	APawn* PlayerTank{ nullptr };
};
