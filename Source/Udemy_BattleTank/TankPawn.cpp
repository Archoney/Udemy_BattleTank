#include "TankPawn.h"

ATankPawn::ATankPawn()
{
	SetCanBeDamaged(true);
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	Health = BaseHealth;
}

float ATankPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	int32 Damage = FPlatformMath::CeilToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(Damage, 0, BaseHealth);
	Health -= DamageToApply;

	if (Health <= 0)
	{
		TankDestroyed.Broadcast();
	}

	return DamageToApply;
}

float ATankPawn::GetHealthPercent() const
{
	return float(Health) / float(BaseHealth);
}
