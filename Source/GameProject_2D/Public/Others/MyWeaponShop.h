// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Interface/OpenFunctionJunction.h"
#include "MyWeaponShop.generated.h"

UCLASS()
class GAMEPROJECT_2D_API AMyWeaponShop : public AActor , public IOpenFunctionJunction
{
	GENERATED_BODY()
	
public:	

	virtual void PlayerEnterShop() override;
	

	AMyWeaponShop();

	UPROPERTY(BlueprintReadwrite,EditAnywhere)
	UBoxComponent* BaseCollision;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPlayerOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);

};
