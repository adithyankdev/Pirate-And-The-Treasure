

#include "Others/MyWeaponShop.h"
#include "PlayerPirate.h"
#include "Kismet/KismetSystemLibrary.h"

void AMyWeaponShop::PlayerEnterShop()
{

}


// Sets default values
AMyWeaponShop::AMyWeaponShop()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoXComponent"));
	SetRootComponent(BaseCollision);
//	BaseCollision->SetCollisionProfileName("OverlapAllDynamics");
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

void AMyWeaponShop::OnPlayerOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor->IsA(APlayerPirate::StaticClass()))
	{
		if(IOpenFunctionJunction* Interface = Cast <IOpenFunctionJunction>(OtherActor))
		{
			
			Interface->PlayerEnterShop();
		}
    }
}

