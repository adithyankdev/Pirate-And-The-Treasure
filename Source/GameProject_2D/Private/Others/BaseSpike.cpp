

#include "Others/BaseSpike.h"
#include "PlayerPirate.h"
#include "Enemy/BaseEnemy.h"


void ABaseSpike::DamageActorInter()
{

}

ABaseSpike::ABaseSpike()
{
	PrimaryActorTick.bCanEverTick = true;
	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	SetRootComponent(RootCapsule);
}

void ABaseSpike::BeginPlay()
{
	Super::BeginPlay();
	RootCapsule->OnComponentBeginOverlap.AddDynamic(this, &ABaseSpike::OnBeginOverlap);
}

void ABaseSpike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseSpike::OnBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && OtherActor->IsA(APlayerPirate::StaticClass()))
	{
		if(APlayerPirate* Player = Cast<APlayerPirate>(OtherActor))
		{
			Player->CallEndWidget();
		}
	}
	else if (OtherActor != this && OtherActor->IsA(ABaseEnemy::StaticClass()))
	{
		if(IDamageInterface* Interface = Cast <IDamageInterface>(OtherActor))
		{
			Interface->DamageActorInter();
		}
	}
}

