// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Interface/PlayerInfoInterface.h"
#include "SpeedPotion.generated.h"

UCLASS()
class GAMEPROJECT_2D_API ASpeedPotion : public AActor , public IPlayerInfoInterface
{
	GENERATED_BODY()
	
public:	
	virtual void CollectingSpeedBoost() override;
	

	ASpeedPotion();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite , EditAnywhere)
	UCapsuleComponent* RootCapsule;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
	void GetDestroyed();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayCollectAnim();

	UFUNCTION()
	void DestroyActor();
};
