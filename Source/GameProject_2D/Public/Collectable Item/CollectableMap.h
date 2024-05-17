// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "CollectableMap.generated.h"

UCLASS()
class GAMEPROJECT_2D_API ACollectableMap : public AActor 
{
	GENERATED_BODY()
	
public:	
	ACollectableMap();


	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	UCapsuleComponent* BaseCollision; 

	UFUNCTION()
	void FuntoDestroy();
	UFUNCTION(BlueprintImplementableEvent)
	void GetDestroyed();
    UFUNCTION(BlueprintImplementableEvent)
	void CollectMapAnimation();
	UFUNCTION(BlueprintImplementableEvent)
	void MapCollected();


	UFUNCTION()
	void PlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweap, const FHitResult& SweapResult);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
