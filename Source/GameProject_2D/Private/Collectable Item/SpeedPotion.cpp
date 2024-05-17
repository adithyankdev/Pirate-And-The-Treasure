// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable Item/SpeedPotion.h"
#include "PlayerPirate.h"
#include "Kismet/KismetSystemLibrary.h"

void ASpeedPotion::CollectingSpeedBoost()
{
}

// Sets default values
ASpeedPotion::ASpeedPotion()
{
	PrimaryActorTick.bCanEverTick = true;
	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	SetRootComponent(RootCapsule);

}

void ASpeedPotion::BeginPlay()
{
	Super::BeginPlay();
	
	RootCapsule->OnComponentBeginOverlap.AddDynamic(this, &ASpeedPotion::OnBeginOverlap);

}

void ASpeedPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpeedPotion::OnBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerPirate::StaticClass()) && OtherComponent == OtherActor->GetRootComponent())
	{
		/*if (APlayerPirate* Player = Cast<APlayerPirate>(OtherActor))
		{
			Player->SpeedBoostCount += 1;
			PlayCollectAnim();
			FTimerHandle CollectPotionTimer;
			GetWorldTimerManager().SetTimer(CollectPotionTimer, this, &ASpeedPotion::DestroyActor, 0.3);
		}*/
		if (IPlayerInfoInterface* Interface = Cast <IPlayerInfoInterface>(OtherActor))
		{
			Interface->CollectingSpeedBoost();
		}

	}
}

void ASpeedPotion::DestroyActor()
{
	GetDestroyed();
	Destroy();

}

