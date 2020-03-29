#include "TankPawn.h"

ATankPawn::ATankPawn()
{
	SetCanBeDamaged(true);
}

float ATankPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 Damage = FPlatformMath::RoundToInt(Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser));
	int32 DamageToApply = FMath::Clamp(Damage, 0, BaseHealth);
	Health -= DamageToApply;
	return DamageToApply;
}

float ATankPawn::GetHealthPercent() const
{
	return float(Health) / float(BaseHealth);
}
