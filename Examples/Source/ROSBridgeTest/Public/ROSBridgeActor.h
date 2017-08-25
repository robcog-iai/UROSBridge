// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Core.h"
#include "GameFramework/Actor.h"
#include "ROSBridgeActor.generated.h"

UCLASS()
class ROSBRIDGETEST_API AROSBridgeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AROSBridgeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
