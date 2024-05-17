// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable Item/CollectableMap.h"
#include "PlayerPirate.h"
#include "Runtime/Engine/Public/TimerManager.h"

ACollectableMap::ACollectableMap()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = BaseCollision; 
	//SetRootComponent(BaseCollision);
	BaseCollision->SetCollisionProfileName("OverlapAllDynamics");

}


void ACollectableMap::FuntoDestroy()
{
	GetDestroyed();
	Destroy();
}

void ACollectableMap::PlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweap, const FHitResult& SweapResult)
{
	if (OtherActor->IsA(APlayerPirate::StaticClass()) and OtherComponent == OtherActor->GetRootComponent())
	{
			CollectMapAnimation();
			MapCollected();
			FTimerHandle timer;
			GetWorldTimerManager().SetTimer(timer, this, &ACollectableMap::FuntoDestroy,0.2);
	}
}

void ACollectableMap::BeginPlay()
{
	Super::BeginPlay();

	BaseCollision->OnComponentBeginOverlap.AddDynamic(this, &ACollectableMap::PlayerBeginOverlap);
	
}

void ACollectableMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

