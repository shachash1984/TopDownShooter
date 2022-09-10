// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingComponent.h"


#include "Projectile.h"
#include "TopDownShooter/TopDownShooterCharacter.h"

// Sets default values for this component's properties
UShootingComponent::UShootingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UShootingComponent::Shoot(FVector& ShootFromLocation, FVector& ShootToLocation) const
{
	//UE_LOG(LogTopDownShooter, Log, TEXT("Shooting from (%f, %f, %f) , To: (%f, %f, %f)"), ShootFromLocation.X, ShootFromLocation.Y, ShootFromLocation.Z, ShootToLocation.X, ShootToLocation.Y, ShootToLocation.Z);
	UWorld* World = GetWorld();
	if (World)
	{
		const auto Owner = static_cast<ATopDownShooterCharacter*>(GetOwner());
		if (Owner)
		{
			if (Owner->GetProjectileClass())
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = Owner;
				SpawnParams.Instigator = Owner->GetInstigator();

				// Spawn the projectile at the muzzle
				AProjectile* Projectile = World->SpawnActor<AProjectile>(Owner->GetProjectileClass(), ShootFromLocation, Owner->GetActorRotation(), SpawnParams);
				
				if (Projectile)
				{
					// Set the projectile's initial trajectory
					FVector LaunchDirection = Owner->GetActorRotation().Vector();
					//float wantedHeight = LaunchDirection.Z;
					//wantedHeight += 0.1f;
					LaunchDirection.SetComponentForAxis(EAxis::Z, 0.0f);
					Projectile->ShootInDirection(LaunchDirection);
				}
			}
		}
		
	}
}


// Called when the game starts
void UShootingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

