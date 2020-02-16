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

	void AimAtCrosshair();

	APawn* GetPlayerTank() const;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetCrosshairPositionOnCanvas(const FVector2D& Position);

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UTankAimingComponent* AimingComponent{ nullptr };

private:
	TOptional<FVector> GetSightRayHitLocation() const;
	TOptional<FVector> GetLookDirection() const;
	TOptional<FVector> GetLookVectorHitLocation(const FVector& LookDirection) const;
	TOptional<FVector2D> CrosshairCanvasPosition;
};
