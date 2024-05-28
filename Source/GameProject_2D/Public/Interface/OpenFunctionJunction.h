// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "OpenFunctionJunction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UOpenFunctionJunction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEPROJECT_2D_API IOpenFunctionJunction
{
	GENERATED_BODY()

public:
	//for Player and Shop
	UFUNCTION()
	virtual void PlayerEnterShop() = 0; 
	


};
