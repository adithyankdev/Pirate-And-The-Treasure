// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h" 
#include "Interface/DamageInterface.h"
#include "Interface/OpenFunctionJunction.h"
#include "BaseEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_2D_API ABaseEnemy : public APaperCharacter , public IDamageInterface 
{
	GENERATED_BODY()


public:

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	float DIFFICULTY;

	UPROPERTY()
	bool Hited;


	//Interface Function 
	virtual void DamageActorInter() override;

	//Interface referance for calling player interface
	IDamageInterface* DamageInter;

	UPROPERTY(BlueprintReadWrite,EditAnyWhere)
	float AtkRangetolarance;

	ABaseEnemy();


	virtual void BeginPlay()override;

	virtual void Tick(float DeltaTime) override;

	//Class Components
	UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
	UBoxComponent* Box;
	UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
	UBoxComponent* HitBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
	UStaticMeshComponent* Point1;
	UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
	UStaticMeshComponent* Point2;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float EnemyPetrolSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float EnemyChaseSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool ToggleLoc;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float EnemyHealth;

	//Storing Petrol location value
	UPROPERTY()
	FVector PetrolLocation;
	//Storing Enemy current Rotation
	UFUNCTION()
	void Rotation();

	//Attack timer
	FTimerHandle AttackTimer;



	//Enemy destroy after hit
	UFUNCTION()
	virtual void CharacterDestroy();

	// Enemy Chase And Vison Capsule Overlap
	UPROPERTY()
	APaperCharacter* Player;


	//Enemy vision collision
	UFUNCTION()
	void OnBeginOverlapVision(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlapVision(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);


	//Enemy behaviour state controlling variable
	UPROPERTY()
	bool IsChasing;
	UPROPERTY()
	bool IsPetrolling;
	UPROPERTY()
	bool IsAttacking;
	UPROPERTY()
	bool LocCheck;


	//Enemy attack range collision
	UFUNCTION()
	void OnBeginOverlapAtk(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlapAtk(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);


	//Play Animation
	UFUNCTION( BlueprintImplementableEvent)
	void PlayAttackAnim();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayHitAnim();

	UFUNCTION(BlueprintImplementableEvent)
	void GetDestroyed();

	
	//Petrol behaviour of the enemy
	UFUNCTION()
	virtual void PetrolLocationCheck();
	UFUNCTION()
	virtual void PetrollingArea();
	UFUNCTION()
	virtual void PetrollingInterval();


	//Enemy Chasing Function
	UFUNCTION()
	virtual void ChasingPlayer();


	//Enemy Attacking Functions
	UFUNCTION()
	virtual void StartAttackPlayer();

	UFUNCTION()
	virtual void AttackingPlayer();

	UFUNCTION()
	virtual void StopAttackingPlayer();

	bool OneTimeAttack;

};
