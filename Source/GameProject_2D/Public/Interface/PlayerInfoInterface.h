// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInfoInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInfoInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEPROJECT_2D_API IPlayerInfoInterface
{
	GENERATED_BODY()

	
public:
	virtual void CollectingSpeedBoost() = 0; 

};


