// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/OneWayPlatform.h"
#include "PlayerPirate.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Public/TimerManager.h"

// Sets default values
AOneWayPlatform::AOneWayPlatform()
{
	UnderRoot = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	SetRootComponent(UnderRoot);

	Platform = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Platform->SetupAttachment(UnderRoot);

}

void AOneWayPlatform::BeginPlay()
{
	Super::BeginPlay();
	UnderRoot->OnComponentBeginOverlap.AddDynamic(this, &AOneWayPlatform::OnBeginOverlap);
	UnderRoot->OnComponentEndOverlap.AddDynamic(this, &AOneWayPlatform::OnEndOverlap);
}

// Called every 
void AOneWayPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOneWayPlatform::EnableCollision()
{
	Platform->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AOneWayPlatform::OnBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerPirate::StaticClass()) && OtherComponent==OtherActor->GetRootComponent())
	{
		Platform->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		FString Tola = TEXT("Overlaped");
		UKismetSystemLibrary::PrintString(GetWorld(), Tola, true, true, FLinearColor::Green);
	}
	
}

void AOneWayPlatform::OnEndOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(APlayerPirate::StaticClass()) && OtherComponent == OtherActor->GetRootComponent())
	{
		FTimerHandle CollectCoinTimer;
		GetWorldTimerManager().SetTimer(CollectCoinTimer, this, &AOneWayPlatform::EnableCollision, 0.1);
		
		FString Tola = TEXT("endOverlaped");
		UKismetSystemLibrary::PrintString(GetWorld(), Tola, true, true, FLinearColor::Red);
	}
	

}

