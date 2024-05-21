

#include "Others/MyWeaponShop.h"
#include "PlayerPirate.h"

void AMyWeaponShop::PlayerEnterShop()
{

}

// Sets default values
AMyWeaponShop::AMyWeaponShop()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoXComponent"));
	RootComponent = BaseCollision;


}

void AMyWeaponShop::BeginPlay()
{
	Super::BeginPlay();

	BaseCollision->OnComponentBeginOverlap.AddDynamic(this, &AMyWeaponShop::OnPlayerOverlap);
	
}

void AMyWeaponShop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyWeaponShop::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool BfromSweap, const FHitResult& SweapResult)
{
	if (OtherActor->IsA(APlayerPirate::StaticClass()))
	{
		if(IOpenFunctionJunction* Interface = Cast <IOpenFunctionJunction>(OtherActor))
		{
			Interface->PlayerEnterShop();
		}
    }
}

