// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable Item/Coin.h"
#include "PlayerPirate.h"

// Sets default values
ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = true;
	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(RootCapsule);

}

void ACoin::BeginPlay()
{
	Super::BeginPlay();
	RootCapsule->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnBeginOverlap);
}

void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoin::OnBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerPirate::StaticClass()) && OtherComponent==OtherActor->GetRootComponent())
	{
		//if (IPlayerInfoInterface* Interface = Cast<IPlayerInfoInterface>(OtherActor))
		//{
			CountingCoin();
		//	Interface->CollectingCoin();
			CollectCoinAnim();
			FTimerHandle CollectCoinTimer;
			GetWorldTimerManager().SetTimer(CollectCoinTimer, this, &ACoin::DestroyActor, 0.4);
		//}
		
   }
}

void ACoin::DestroyActor()
{
	GetDestroyed();
	Destroy();
}

