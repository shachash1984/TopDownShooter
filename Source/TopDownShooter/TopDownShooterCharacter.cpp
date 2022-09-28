// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownShooterCharacter.h"
#include "ShootingComponent.h"
#include "Projectile.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Net/UnrealNetwork.h"

ATopDownShooterCharacter::ATopDownShooterCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	bReplicates = true;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->SetNetAddressable();
	GetCharacterMovement()->SetIsReplicated(true);
	
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a shooting component
	ShootingComponent = CreateDefaultSubobject<UShootingComponent>(TEXT("Shooting"));
	ShootingComponent->SetNetAddressable();
	ShootingComponent->SetIsReplicated(true);

	// Set Muzzle offset
	MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATopDownShooterCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

TSubclassOf<AProjectile> ATopDownShooterCharacter::GetProjectileClass() const
{
	return ProjectileClass;
}

void ATopDownShooterCharacter::RotateToCursor_Implementation(const FVector& MouseCursor)
{
	FRotator wantedRotation = GetActorRotation();
	FVector lookDir = MouseCursor - GetActorLocation();
	if (lookDir.Normalize())
	{
		// convert FVector to rotation
		const float yaw = FMath::RadiansToDegrees(FMath::Atan2(lookDir.Y, lookDir.X));
		wantedRotation.SetComponentForAxis(EAxis::Z, yaw);
	}
	
	bool bSuccess = SetActorRotation(wantedRotation);
	UE_LOG(LogTemp, Warning, TEXT("RotateToCursor_Implementation: %d"), bSuccess);
}


void ATopDownShooterCharacter::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATopDownShooterCharacter, ShootingComponent);
}
