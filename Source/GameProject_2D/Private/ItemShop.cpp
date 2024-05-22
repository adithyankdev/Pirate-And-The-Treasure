

#include "ItemShop.h"
#include "PlayerPirate.h"



AItemShop::AItemShop()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BaseCollision);

}



void AItemShop::BeginPlay()
{
	Super::BeginPlay();

	BaseCollision->OnComponentBeginOverlap.AddDynamic(this, &AItemShop::OnPlayerEnterOverlap);
	
}

void AItemShop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemShop::OnPlayerEnterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweap, const FHitResult& SweapResultf)
{
	
}