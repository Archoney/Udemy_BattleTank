#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDestroyedDelegate);

UCLASS()
class UDEMY_BATTLETANK_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	ATankPawn();

	void BeginPlay() override;

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION(BlueprintPure, Category = "Status")
	float GetHealthPercent() const;

	FTankDestroyedDelegate TankDestroyed;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 BaseHealth {100};

	UPROPERTY(VisibleAnywhere, Category = "Status")
	int32 Health {BaseHealth};
};
