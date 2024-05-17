// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "OneWayPlatform.generated.h"

UCLASS()
class GAMEPROJECT_2D_API AOneWayPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	AOneWayPlatform();

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly , VisibleAnywhere)
	UBoxComponent* UnderRoot;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UPaperSpriteComponent* Platform;

	UFUNCTION()
	void EnableCollision();


	//For Passing The Way 
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
};
