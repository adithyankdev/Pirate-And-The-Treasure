// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckPointFlag.generated.h"

UCLASS()
class GAMEPROJECT_2D_API ACheckPointFlag : public AActor
{
	GENERATED_BODY()
	
public:	
	ACheckPointFlag();

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

};
