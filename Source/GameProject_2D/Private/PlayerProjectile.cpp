// MyActor.cpp

#include "PlayerProjectile.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Enemy/BaseEnemy.h"
#include "Cannons/Base/BaseCannon.h"
#include "PlayerPirate.h"

void APlayerProjectile::DamageActorInter()
{

}



// Sets default values
APlayerProjectile::APlayerProjectile()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create and attach a capsule component for collision
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    RootComponent = CapsuleComponent;
    CapsuleComponent->SetCollisionProfileName("BlockAllDynamic");
    CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerProjectile::OnOverlapBegin);

    // Create a projectile movement component
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 600.f;
    ProjectileMovement->MaxSpeed = 700.f;
    ProjectileMovement->bConstrainToPlane = true;
    ProjectileMovement->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);
    ProjectileMovement->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void  APlayerProjectile::BeginPlay()
{
    Super::BeginPlay();

    FTimerHandle Timertodestroy;
    GetWorldTimerManager().SetTimer(Timertodestroy, this, &APlayerProjectile::AutoDestroy, 3);
}

// Called every frame
void  APlayerProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void  APlayerProjectile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    if (OtherActor != this && OtherComp == OtherActor->GetRootComponent())
    {
        if (OtherActor->IsA(ABaseEnemy::StaticClass()) || OtherActor->IsA(ABaseCannon::StaticClass()))
        {
            FString debug = TEXT("Ovelapped bro");
            UKismetSystemLibrary::PrintString(GetWorld(), debug);

            if (IDamageInterface* ActorInterfacee = Cast<IDamageInterface>(OtherActor))
            {
                ActorInterfacee->DamageActorInter();
                Destroy();
            }
        }
        
     
    }
   
}

void APlayerProjectile::AutoDestroy()
{
    Destroy();
}


