// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBehaviour.h"
#include "TopDownShooter/TopDownShooter.h"

// Sets default values
APlayerBehaviour::APlayerBehaviour()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTopDownShooter, Log, TEXT("PlayerBehaviour Ctor"));
}

// Called when the game starts or when spawned
void APlayerBehaviour::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTopDownShooter, Log, TEXT("PlayerBehaviour BeginPlay"));
	
}

// Called every frame
void APlayerBehaviour::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Count++;
	if (Count % 100 == 0)
	{
		UE_LOG(LogTopDownShooter, Log, TEXT("PlayerBehaviour Tick"));
	}
}

