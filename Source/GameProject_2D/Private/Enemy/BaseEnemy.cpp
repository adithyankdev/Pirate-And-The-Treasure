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
	//hard value will be negative so  , for increase the speed  ( - -  == + )
	EnemyChaseSpeed(0.6f - DIFFICULTY),
	EnemyPetrolSpeed(0.3f - DIFFICULTY)

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

	Rotation();
	//Adding diffuculty to increase enemy atk range for hard option
	float Tolarance = 1.0f-DIFFICULTY;
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
	//Difficulty added with multiply 10 due to int value
	GetWorldTimerManager().SetTimer(PetorlLocCheckTimer, this, &ABaseEnemy::PetrolLocationCheck, 3+(DIFFICULTY*10));
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
	//Not Converting to int  , because   it can lead to negative value (unexpected behaviour)
	GetWorldTimerManager().SetTimer(AttackTimer, this, &ABaseEnemy::AttackingPlayer, 0.7+DIFFICULTY, true);
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
		FTimerHandle Visionendtimer;
		//Hard Option  = -0.2  therefore  subraing the value which lead to add  -- for more time on stop when player is out of vision
		GetWorldTimerManager().SetTimer(Visionendtimer, this, &ABaseEnemy::PetrolLocationCheck, (3-DIFFICULTY*10));
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
