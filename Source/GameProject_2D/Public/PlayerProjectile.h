
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interface/DamageInterface.h"
#include "PlayerProjectile.generated.h"

UCLASS()
class GAMEPROJECT_2D_API APlayerProjectile : public AActor , public IDamageInterface
{
   GENERATED_BODY()

public:

    virtual void DamageActorInter();

    APlayerProjectile();

protected:
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere)
    UCapsuleComponent* CapsuleComponent;

    UPROPERTY(VisibleAnywhere)
    UProjectileMovementComponent* ProjectileMovement;

    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
        class AActor* OtherActor,
        class UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

    UFUNCTION()
    void AutoDestroy();


};