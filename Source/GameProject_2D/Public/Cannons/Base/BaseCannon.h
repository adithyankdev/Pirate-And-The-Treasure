// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "PlayerPirate.h"
#include "Interface/DamageInterface.h"
#include "BaseCannon.generated.h"

UCLASS()
class GAMEPROJECT_2D_API ABaseCannon : public AActor , public IDamageInterface
{
	GENERATED_BODY()
	
public:	

	virtual void DamageActorInter() override;
	

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	float DIFFICULTY;

	ABaseCannon();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadwrite, EditAnywhere, Category = Cannon)
	float CannonHealth;

	UPROPERTY(BlueprintReadonly, EditAnywhere , Category = Cannon)
	TSubclassOf<AActor>Bullet;

	UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
	UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
	UCapsuleComponent* RootCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
	UBoxComponent* AttackBox;


	FTimerHandle ProjectileTimerHandle;

	UFUNCTION()
	void StartProjectile();

	UFUNCTION()
	void ShootProjectile();

	UFUNCTION()
	void StopProjectile();
	
	//UPROPERTY(BlueprintReadOnly)
	//bool CanShoot;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	UFUNCTION()
	void ProceedDestroy();

	//For Animation
	UFUNCTION()
	void ProceedFire();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayAttackAnim();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayHitAnim();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayDeadAnim();

	


};
