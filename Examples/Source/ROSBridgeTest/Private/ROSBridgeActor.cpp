// Fill out your copyright notice in the Description page of Project Settings.

#include "ROSBridgeActor.h"
#include "ROSBridgeTest.h"


// Sets default values
AROSBridgeActor::AROSBridgeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    UE_LOG(LogTemp, Log, TEXT("Actor Generated."));
	PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 1.0f / 30.0f;
}

// Called when the game starts or when spawned
void AROSBridgeActor::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Actor BeginPlay() Called."));
}

// Called every frame
void AROSBridgeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    UE_LOG(LogTemp, Log, TEXT("Actor Ticks, DeltaSeconds = %.3f."), DeltaTime);
}
