// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannons/Base/BaseCannon.h"
#include "Kismet/KismetSystemLibrary.h"

void ABaseCannon::DamageActorInter()
{
	 PlayHitAnim();
	 CannonHealth -= 0.1f;
	FString Debug = TEXT("Get Hit");
	UKismetSystemLibrary::PrintString(GetWorld(), Debug,true ,true,FLinearColor::Red);
	
	//add the difficulty here
	
	if (CannonHealth < 0.0)
	{
		PlayDeadAnim();
		FTimerHandle DestroyProceed;
		GetWorldTimerManager().SetTimer(DestroyProceed, this, &ABaseCannon::ProceedDestroy, 2);
	}
	
}

  

void ABaseCannon::ProceedDestroy()
{
	Destroy();
}



ABaseCannon::ABaseCannon()
{
	PrimaryActorTick.bCanEverTick = true;

	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootCapsule"));
	RootComponent = RootCapsule;

	AttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AtkRangeBox"));
	AttackBox->SetupAttachment(RootCapsule);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DirectionArrow"));
	Arrow->SetupAttachment(RootCapsule);

	//CanShoot = true; 


}

void ABaseCannon::BeginPlay()
{
	CannonHealth = 0.3f;
	AttackBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseCannon::OnBeginOverlap);
	AttackBox->OnComponentEndOverlap.AddDynamic(this, &ABaseCannon::OnEndOverlap);
	Super::BeginPlay();
	
}

void ABaseCannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Add The Diffculty to timer
void ABaseCannon::StartProjectile()
{
	//if (CanShoot)
	//{
		GetWorldTimerManager().SetTimer(ProjectileTimerHandle, this, &ABaseCannon::ShootProjectile, 0.5, true);
	//}                                                                                                          
	
}                                                 

void ABaseCannon::ShootProjectile()
{
	PlayAttackAnim();
	FTimerHandle FireAnimTimer;
	GetWorldTimerManager().SetTimer(FireAnimTimer, this, &ABaseCannon::ProceedFire, 0.3+DIFFICULTY);
	
	
}

void ABaseCannon::ProceedFire()
{
	
	FVector Location = Arrow->GetComponentLocation();
	FRotator Rotation = Arrow->GetComponentRotation();
	if (AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(Bullet, Location, Rotation))
	{
		if (SpawnedActor)
		{
			UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(SpawnedActor->GetRootComponent());
			FVector ImpulseDirection = Arrow->GetForwardVector();
			float force = 1000.0f;
			RootComp->AddImpulse(ImpulseDirection * force);

		}
	}
	
}



void ABaseCannon::StopProjectile()
{                                                                                                             
	GetWorldTimerManager().ClearTimer(ProjectileTimerHandle);
}
                                                                    
//Overlap Events
void ABaseCannon::OnBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerPirate::StaticClass()))
	{
		//CanShoot = true; 
		StartProjectile();
	}
	

}

void ABaseCannon::OnEndOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(APlayerPirate::StaticClass()))
	{
		//CanShoot = false;
		StopProjectile();
	}
	

}

