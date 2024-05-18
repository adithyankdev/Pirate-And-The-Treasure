// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Coin.generated.h"

UCLASS()
class GAMEPROJECT_2D_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	


	ACoin();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadwrite , VisibleAnywhere )
	UCapsuleComponent* RootCapsule;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void DestroyActor();

	//Play Collect Anim
	UFUNCTION(BlueprintImplementableEvent)
	void CollectCoinAnim();

	UFUNCTION(BlueprintImplementableEvent)
	void GetDestroyed();

	UFUNCTION(BlueprintImplementableEvent)
	void CountingCoin();

};
