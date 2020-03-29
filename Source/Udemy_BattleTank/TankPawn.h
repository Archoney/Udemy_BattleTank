#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

UCLASS()
class UDEMY_BATTLETANK_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	ATankPawn();

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 BaseHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Status")
	int32 Health = BaseHealth;
};
