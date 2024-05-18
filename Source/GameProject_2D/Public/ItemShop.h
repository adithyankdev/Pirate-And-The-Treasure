
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Interface/OpenFunctionJunction.h"
#include "ItemShop.generated.h"

UCLASS()
class GAMEPROJECT_2D_API AItemShop : public AActor , public IOpenFunctionJunction
{
	GENERATED_BODY()
	
public:	
	
	virtual void PlayerEnterShop() override;

	AItemShop();

	UPROPERTY(BlueprintReadWrite , EditAnywhere)
	UBoxComponent* BaseCollision;
	
	UFUNCTION()
	void OnPlayerEnterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweap, const FHitResult& SweapResultf);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayerEntered();


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
