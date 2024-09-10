// Fill out your copyright notice in the Description page of Project Settings.


#include "Maze/CarBoulderEvent.h"


// Sets default values
ACarBoulderEvent::ACarBoulderEvent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
}

// Called when the game starts or when spawned
void ACarBoulderEvent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACarBoulderEvent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

