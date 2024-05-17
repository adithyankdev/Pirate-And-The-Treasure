// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannons/Base/BaseCannonBullet.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerPirate.h"
#include "Enemy/BaseEnemy.h"

#include "Runtime/Engine/Public/TimerManager.h"


ABaseCannonBullet::ABaseCannonBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootCapsule"));
	SetRootComponent(RootCapsule);  

}

void ABaseCannonBullet::BeginPlay()
{
	Super::BeginPlay();

	RootCapsule->OnComponentBeginOverlap.AddDynamic(this, &ABaseCannonBullet::OnBeignOverlap);
	FTimerHandle DeleteTimer;
	GetWorldTimerManager().SetTimer(DeleteTimer, this, &ABaseCannonBullet::DestroyActor, 3);
	
	
}

void ABaseCannonBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCannonBullet::DestroyActor()
{
	Destroy();
}

void ABaseCannonBullet::OnBeignOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerPirate::StaticClass()) && OtherComponent==OtherActor->GetRootComponent())
	{
		if (IDamageInterface* Interface = Cast<IDamageInterface>(OtherActor))
		{
			Interface->DamageActorInter();
			Destroy();
		}
	} 
	else if (OtherActor -> IsA(ABaseEnemy::StaticClass()) && OtherComponent == OtherActor->GetRootComponent())
	{
		if (IDamageInterface* Interface = Cast <IDamageInterface>(OtherActor))
		{
			Interface->DamageActorInter();
			Destroy();
		}
	}
	//Give Hit Damage to enemy Also 

}

