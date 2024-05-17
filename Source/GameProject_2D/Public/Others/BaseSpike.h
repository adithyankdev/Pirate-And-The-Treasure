// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Interface/DamageInterface.h"
#include "BaseSpike.generated.h"

UCLASS()
class GAMEPROJECT_2D_API ABaseSpike : public AActor  , public IDamageInterface
{
	GENERATED_BODY()
	
public:	

	virtual void DamageActorInter() override;


	ABaseSpike();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadwrite , EditAnywhere)
	UCapsuleComponent* RootCapsule;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);

};
