

#include "ItemShop.h"
#include "PlayerPirate.h"

void AItemShop::PlayerEnterShop()
{

}

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
	if (OtherActor->IsA(APlayerPirate::StaticClass()))
	{
		if (IOpenFunctionJunction* Interface = Cast<IOpenFunctionJunction>(OtherActor))
		{
			Interface->PlayerEnterShop();
		}
	}
}