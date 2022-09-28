// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	void virtual GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sphere collision component
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile, Replicated)
	USphereComponent* CollisionComponent;

	// Projectile mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile, Replicated)
	UStaticMeshComponent* ProjectileMeshComponent;

	UPROPERTY(EditAnywhere, Category = Projectile)
	float InitialSpeed{1000.0f};

	// Projectile movement component
	UPROPERTY(VisibleAnywhere, Category = Movement, Replicated)
	UProjectileMovementComponent* ProjectileMovementComponent;	

	// Projectile Material
	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
	UMaterialInstanceDynamic* ProjectileMaterialInstance;

	// Function that initializes the projectile's velocity in the shooting direction
	void ShootInDirection(const FVector& ShootDirection);
};
