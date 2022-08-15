// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDownShooterCharacter.generated.h"

UCLASS(Blueprintable)
class ATopDownShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATopDownShooterCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns ShootingComponent subobject **/
	FORCEINLINE class UShootingComponent* GetShootingComponent() const { return ShootingComponent; }

	/** Returns the Projectile class*/
	TSubclassOf<class AProjectile> GetProjectileClass() const;

	// Gun muzzle offset from the character location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;
private:

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))

	class USpringArmComponent* CameraBoom;
protected:

	/** Component responsible for shooting */
	UPROPERTY(VisibleAnywhere, Category = Shooting)
	class UShootingComponent* ShootingComponent;

	/** Projectile class to spawn*/
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	
};

