// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "BaseCannonBullet.generated.h"

UCLASS()
class GAMEPROJECT_2D_API ABaseCannonBullet : public AActor 
{
	GENERATED_BODY()
	
public:	
	
	ABaseCannonBullet();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadwrite ,  EditAnywhere)
	UCapsuleComponent* RootCapsule;

	UFUNCTION()
	void DestroyActor();

	UFUNCTION()
	void OnBeignOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,int32 OtherBodyIndex , bool FromSweep , const FHitResult& SweepResult);

};
