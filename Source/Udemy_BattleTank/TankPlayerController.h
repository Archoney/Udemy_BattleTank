#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

UCLASS()
class UDEMY_BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void AimingComponentReady(UTankAimingComponent* AimingComponent);

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetCrosshairPositionOnCanvas(const FVector2D& Position);

private:
	UTankAimingComponent* AimingComponent{ nullptr };

	TOptional<FVector> GetSightRayHitLocation() const;
	TOptional<FVector> GetLookDirection() const;
	TOptional<FVector> GetLookVectorHitLocation(const FVector& LookDirection) const;
	TOptional<FVector2D> CrosshairCanvasPosition;
};
