// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPirate.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
//#include "Projectile/Projectile_Throw.h"
#include "Runtime/Engine/Public/TimerManager.h"

//Interface Function Implementation
void APlayerPirate::DamageActorInter()
{
	//SetActorTickEnabled(false);
	APlayerPirate::DisableInput(PirateController);
	if (!ishit)PlayHitAnim(); ishit = true;
	FTimerHandle timer;
	GetWorldTimerManager().SetTimer(timer, this, &APlayerPirate::Callingtimerwidget, 1);
		
	
}

void APlayerPirate::Callingtimerwidget()
{
	CallEndWidget();
}





//Constructor
APlayerPirate::APlayerPirate()
{


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("Projectile Point"));
	ArrowComp->SetupAttachment(RootComponent);

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackBox"));
	HitBox->SetupAttachment(RootComponent);

	PirateController = NULL;
	//Coins = 0;
	MovementSpeed = 0.6f;
	IsJumping = false;

	ZRotation = true;

	CollectabelMap = 0; 

}

//Begin Play ()
void APlayerPirate::BeginPlay()
{
	 PirateController = Cast<APlayerController>(GetController());

	Enemycount = 0; 
	Super::BeginPlay();

	ProjectileCount = 3;

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerPirate::OnBeginOverlapAtk);
	//	HitBox->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnEndOverlapAtk);
	HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//HitBox->SetVisibility(false);

	if (PirateController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PirateController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PirateMappingContext, 0);
		}
	}

}





void APlayerPirate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


//Checking Is the player is on Ground for allowing The jump 
bool APlayerPirate::IsOnGround()
{
	FHitResult HitResult;
	FVector Start = GetActorLocation();
	FVector End = ((GetActorUpVector() * -1) * 30.0f) + Start;
	ECollisionChannel CollisionChannel = ECC_Visibility;
	FCollisionQueryParams TraceParams;

	bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, CollisionChannel, TraceParams);

	if (IsHit)return true;

	return false;
}


void APlayerPirate::CollectingSpeedBoost()
{
	SpeedBoostCount += 1;
}




//Checking the current Z rotation for Adding Projectile impulse
bool APlayerPirate::CurrentRotation()
{
	FRotator CurrentRotation = GetActorRotation();
	return FMath::IsNearlyZero(CurrentRotation.Yaw, KINDA_SMALL_NUMBER);
}

// Seting Jumpping to false (Successfully Jumped)
void APlayerPirate::CharacterJumping()
{
	IsJumping = false;
}

//Disabling Input for avoid spamming
void APlayerPirate::DisableInputFalse()
{
	//APlayerController* PirateController = Cast<APlayerController>(GetController());
	APlayerPirate::EnableInput(PirateController);
	AtkPressed = false;
	HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

//player jumping Function
void APlayerPirate::JumpFunction(const FInputActionValue& InputValue)
{
	bool JumpValue = InputValue.Get<bool>();
	if (JumpValue)
	{
		if (IsJumping == false)
		{
			if (IsOnGround())
			{
				IsJumping = true;
				FVector JumpVelocity = GetActorUpVector() * 700.0f;
				LaunchCharacter(JumpVelocity, false, false);

				FTimerHandle TimerHandle;
				GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerPirate::CharacterJumping, 0.5);

			}
		}
	}
}

//Player Vertical Move Function
void APlayerPirate::MoveFunction(const FInputActionValue& InputValue)
{
	const float MovementValue = InputValue.Get<float>();

	if (MovementValue < 0)
	{
		ZRotation = false;
		Controller->SetControlRotation(FRotator(0.0f, 180.0f, 0.0f));
		FRotator Rotation = { 0,Controller->GetControlRotation().Yaw,0 };
		FVector Direction = Rotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(Direction, MovementSpeed);
	}
	if (MovementValue > 0)
	{
		ZRotation = true;
		Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		FRotator Rotation = { 0,Controller->GetControlRotation().Yaw,0 };
		FVector Direction = Rotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(Direction, MovementSpeed);
	}
}

// Attack 1 Function 
void APlayerPirate::AttackOne(const FInputActionValue& InputValue)
{
	bool Value = InputValue.Get<bool>();
	AtkPressed = true;
	PlayAttackAnim();
	HitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	if (Value)
	{
		//APlayerController* PirateController = Cast<APlayerController>(GetController());
		APlayerPirate::DisableInput(PirateController);

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerPirate::DisableInputFalse, 0.3);

	}

	//HitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}


//Attack Range Check to Damage Enemy (BeginOverlap)
void APlayerPirate::OnBeginOverlapAtk(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (AtkPressed)
	{
		if (OtherActor != this && OtherComponent==OtherActor->GetRootComponent())
		{
			if (OtherActor->IsA(APaperCharacter::StaticClass()) ||OtherActor->IsA(AActor::StaticClass()))
			{
				if (IDamageInterface* Interface = Cast<IDamageInterface>(OtherActor))
				{
					Interface->DamageActorInter();
				}
			}
			
		}
	}
}

void APlayerPirate::OnEndOverlapAtk(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	AtkPressed = false; 
}

//Projectile Throwing Function
void APlayerPirate::ThrowProjectile(const FInputActionValue& InputValue)
{

	bool value = CurrentRotation();
	if (ProjectileCount != 0)
	{

		FVector Location = ArrowComp->GetComponentLocation();
		FRotator Rotation = ArrowComp->GetComponentRotation();

		 GetWorld()->SpawnActor<AActor>(ActorToSpawn, Location, Rotation);
		
		}
		

	
}

void APlayerPirate::SpeedBoostFunction(const FInputActionValue& InputValue)
{
	if (SpeedBoostCount > 0 && !CanBoost)
	{
		CanBoost = true;
		SpeedBoostCount -= 1;
		MovementSpeed += 0.2f;
		FTimerHandle SpeedBoostExpireTimer;
		FString Tola = TEXT("Speed Boosted ");
		UKismetSystemLibrary::PrintString(GetWorld(), Tola, true, true, FLinearColor::Red);
		GetWorldTimerManager().SetTimer(SpeedBoostExpireTimer, this, &APlayerPirate::SpeedBoostFinish, 5);
	}
	
}

void APlayerPirate::SpeedBoostFinish()
{
	MovementSpeed -= 0.2f;
	FString Tola = TEXT("Speed Boost Finished ");
	UKismetSystemLibrary::PrintString(GetWorld(), Tola, true, true, FLinearColor::Blue);
	CanBoost = false; 
}


//Player Input Bind Function 
void APlayerPirate::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPirate::MoveFunction);
		EnhancedComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerPirate::JumpFunction);
		EnhancedComponent->BindAction(Attack1, ETriggerEvent::Triggered, this, &APlayerPirate::AttackOne);
		EnhancedComponent->BindAction(Projectile, ETriggerEvent::Completed, this, &APlayerPirate::ThrowProjectile);
		EnhancedComponent->BindAction(SpeedBoost, ETriggerEvent::Completed, this, &APlayerPirate::SpeedBoostFunction);
	}
}

