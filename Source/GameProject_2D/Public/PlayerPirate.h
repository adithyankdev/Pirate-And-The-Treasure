// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Components/CapsuleComponent.h"
//#include "Components/SceneComponent.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "InputMappingContext.h"
//#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interface/DamageInterface.h"
#include "Interface/OpenFunctionJunction.h"
#include "PlayerPirate.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_2D_API APlayerPirate : public APaperCharacter , public IDamageInterface , public IOpenFunctionJunction
{
	GENERATED_BODY()
	
public:
	//Interface Function
	UFUNCTION()
	virtual void DamageActorInter() override;
    UFUNCTION()
	virtual void PlayerEnterShop() override; 
	

	APlayerPirate();

	void BeginPlay();

	virtual void Tick(float DeltaTime) override;


	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = PirateFeature)
	int32 Enemycount;

	//Projectile Actor Reference
	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = PirateFeature)
	TSubclassOf<AActor>ActorToSpawn;

	//Projectile Spwaning Point
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UArrowComponent* ArrowComp;

	UPROPERTY(BlueprintReadwrite, EditAnywhere, Category = PirateFeature)
	int32 ProjectileCount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PirateFeature)
	float MovementSpeed;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = PirateFeature)
	int32 CollectabelMap;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = PirateFeature)
	int32 SpeedBoostCount;

	UPROPERTY()
	bool IsJumping;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = EnhancedInput)
	UInputMappingContext* PirateMappingContext;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = EnhancedInput)
	UInputAction* MoveAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = EnhancedInput)
	UInputAction* JumpAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = EnhancedInput)
	UInputAction* Attack1;


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = EnhancedInput)
	UInputAction* SpeedBoost;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = EnhancedInput)
	UInputAction* EnterToStore;

	UPROPERTY()
	bool AtkPressed;

	UPROPERTY()
	bool CanEnterShop;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = EnhancedInput)
	UInputAction* Projectile;

	UPROPERTY(BlueprintReadwrite)
	bool ZRotation;

	//Attack Range
	UPROPERTY(BlueprintReadwrite, EditAnywhere)
	UBoxComponent* HitBox;

	UFUNCTION()
	void OnBeginOverlapAtk(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlapAtk(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	UFUNCTION()
	bool IsOnGround();

	UFUNCTION()
	bool CurrentRotation();

	UFUNCTION()
	void CharacterJumping();

	APlayerController* PirateController;

	//Disable Input for Not Spamming
	UFUNCTION()
	void DisableInputFalse();

	UFUNCTION()
	void Callingtimerwidget();

	UFUNCTION(BlueprintImplementableEvent)
	void CallEndWidget();

	UFUNCTION()
	void JumpFunction(const FInputActionValue& InputValue);
	UFUNCTION()
	void MoveFunction(const FInputActionValue& InputValue);
	UFUNCTION()
	void AttackOne(const FInputActionValue& InputValue);
	UFUNCTION()
	void ThrowProjectile(const FInputActionValue& InputValue);
	UFUNCTION()
	void SpeedBoostFunction(const FInputActionValue& InputValue);
	UFUNCTION()
	void PlayerToEnterShop(const FInputActionValue& InputValue);

	UFUNCTION()
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Play Animation
	UFUNCTION(BlueprintImplementableEvent)
	void PlayHitAnim();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayAttackAnim();

	//SpeedBoost Finish Function 
	UPROPERTY()
	bool CanBoost = false;
	UPROPERTY()
	bool GotHit = false;

	UFUNCTION()
	void SpeedBoostFinish();

	UFUNCTION(BlueprintImplementableEvent)
	void ActivateSpeedBoost();

	UFUNCTION(BlueprintImplementableEvent)
	void ShopWidgetTrigger();

	UFUNCTION(BlueprintImplementableEvent)
	void ProjectileShooted();

	UFUNCTION(BlueprintImplementableEvent)
	void SpeedPotionUsed();

};
