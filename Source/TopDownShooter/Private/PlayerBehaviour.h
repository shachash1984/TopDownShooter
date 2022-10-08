// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerBehaviour.generated.h"

UCLASS()
class APlayerBehaviour : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerBehaviour();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int Count{ 0 };

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
