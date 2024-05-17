// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BaseEnemy.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "PlayerPirate.h"


// DetachmentRules For PetrolPoint(StaicMesh)
FDetachmentTransformRules detachmentrules(
	EDetachmentRule::KeepWorld,
	EDetachmentRule::KeepWorld,
	EDetachmentRule::KeepWorld,
	true
);

//Interface Function  Implementation
void ABaseEnemy::DamageActorInter()
{
	SetActorTickEnabled(false);
	
	PlayHitAnim();
	FTimerHandle Destroytimer;
	GetWorldTimerManager().SetTimer(Destroytimer, this, &ABaseEnemy::CharacterDestroy, 2);

}

void ABaseEnemy::CharacterDestroy()
{
	GetDestroyed();
	Destroy();
}


//Constructor
ABaseEnemy::ABaseEnemy()

	: ToggleLoc(true),
	EnemyChaseSpeed(0.6f),
	EnemyPetrolSpeed(0.3f)

{

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackRange"));
	HitBox->SetupAttachment(RootComponent);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Vision"));
	Box->SetupAttachment(HitBox);

	Point1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	Point1->SetupAttachment(RootComponent);

	Point2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));
	Point2->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;


}

//Begin Play
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.TickInterval = 0.001f;

	Player = nullptr;
	DamageInter = nullptr;

	IsPetrolling =true;
	IsChasing = false; 
	IsAttacking = false;
	LocCheck = true; 

	HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy::OnBeginOverlapAtk);
	HitBox->OnComponentEndOverlap.AddDynamic(this, &ABaseEnemy::OnEndOverlapAtk);

	Box->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy::OnBeginOverlapVision);
	Box->OnComponentEndOverlap.AddDynamic(this, &ABaseEnemy::OnEndOverlapVision);

	Point1->DetachFromComponent(detachmentrules);
	Point2->DetachFromComponent(detachmentrules);

	//PetrolLoc();
	//PetrolLocationCheck();

}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsPetrolling and !IsAttacking)PetrolLocationCheck();
	 if (IsChasing and !IsAttacking)ChasingPlayer();

}

void ABaseEnemy::Rotation()
{

	FVector  Velocity = GetVelocity();
	if (Velocity.X != 0)
	{
		if (Velocity.X > 0)
		{
			SetActorRotation(FRotator(0, 0, 0));
		}
		else
		{
			SetActorRotation(FRotator(0, 180, 0));
		}
	}


}
void ABaseEnemy::PetrolLocationCheck()
{
	if (LocCheck)
	{
		PetrolLocation = ToggleLoc ? Point1->GetComponentLocation() : Point2->GetComponentLocation();
		ToggleLoc = !ToggleLoc;
		LocCheck = false;
		if (!IsPetrolling)IsPetrolling = true;
	}

	PetrollingArea();

}

void ABaseEnemy::PetrollingArea()
{
	//FString debug = TEXT("Hello Petroling");
	//UKismetSystemLibrary().PrintString(GetWorld(), debug);

	Rotation();
	float Tolarance = 1.0f;
	FVector ActorLocation = this->GetActorLocation();

	FVector Direction = (PetrolLocation - ActorLocation).GetSafeNormal();

	AddMovementInput(Direction, EnemyPetrolSpeed);

	if (abs(PetrolLocation.X - ActorLocation.X) <= Tolarance)
	{
		IsPetrolling = false;
		PetrollingInterval();
	}
}
void ABaseEnemy::PetrollingInterval()
{
	LocCheck = true;
	FTimerHandle PetorlLocCheckTimer;
	GetWorldTimerManager().SetTimer(PetorlLocCheckTimer, this, &ABaseEnemy::PetrolLocationCheck, 3);
}


void ABaseEnemy::ChasingPlayer()
{
	
	Rotation();
	FVector PlayerLocation = Player->GetActorLocation();
	FVector Direction = (PlayerLocation - GetActorLocation()).GetSafeNormal();
	AddMovementInput(Direction, EnemyChaseSpeed);
	if(!IsChasing)IsChasing = true;

}


void ABaseEnemy::StartAttackPlayer()
{
	GetWorldTimerManager().SetTimer(AttackTimer, this, &ABaseEnemy::AttackingPlayer, 1, true);
}

void ABaseEnemy::AttackingPlayer()
{
	if (DamageInter == nullptr)
	{
		DamageInter = Cast<IDamageInterface>(Player);
	}
	if (DamageInter != nullptr)
	{
		PlayAttackAnim();
		DamageInter->DamageActorInter();
	}
}

void ABaseEnemy::StopAttackingPlayer()
{
	GetWorldTimerManager().ClearTimer(AttackTimer);
	ChasingPlayer();
	//IsChasing = true;
	//
}


//Enemy VisonBox Overlap
void ABaseEnemy::OnBeginOverlapVision(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && OtherActor->IsA(APlayerPirate::StaticClass()))
	{
		IsPetrolling = false;
		HitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		if (Player == nullptr)
		{
			Player = Cast<APaperCharacter>(OtherActor);
		}
		IsChasing = true;

	}

}

//Enemy VisonBox EndOverlap
void ABaseEnemy::OnEndOverlapVision(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{

	if (OtherActor != nullptr && OtherActor == Player)
	{

		IsChasing = false;
		HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		if (!LocCheck)LocCheck = true;
		//Add DIFFICULTY to the sec in the Timer
		FTimerHandle Visionendtimer;
		GetWorldTimerManager().SetTimer(Visionendtimer, this, &ABaseEnemy::PetrolLocationCheck, 3);
		FString debug = TEXT("Vison Ended");
		UKismetSystemLibrary::PrintString(GetWorld(), debug, true, true, FLinearColor::Red, 2);
	}


}

//Enemy Attack Range Checking (BeginOverlap)
void ABaseEnemy::OnBeginOverlapAtk(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && OtherComponent == OtherActor->GetRootComponent())
	{
		if (OtherActor->IsA(APlayerPirate::StaticClass()))
		{
			if(IsChasing)IsChasing = false;
			if (IsPetrolling)IsPetrolling = false; 
			IsAttacking = true;
			StartAttackPlayer();

		}

	}


}

//Enemy Attack Range Checking (EndOverlap)
void ABaseEnemy::OnEndOverlapAtk(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != this && OtherActor->IsA(APlayerPirate::StaticClass()))
	{
		IsAttacking = false;
	 	StopAttackingPlayer();
		//	StartChasingPlayer();

	}
}
