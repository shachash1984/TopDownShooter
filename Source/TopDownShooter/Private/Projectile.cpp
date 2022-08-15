// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    if (!RootComponent)
    {
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
    }

    if (!CollisionComponent)
    {
	    // Use a sphere as a simple collision representation
        CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
        // Set the sphere's collision radius
        CollisionComponent->SetSphereRadius(15.0f);
        // Set the Root component to be the collision component
        RootComponent = CollisionComponent;
    }

    if (!ProjectileMovementComponent)
    {
	    // Use this component to drive this projectile's movement
        ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
        ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
        //ProjectileMovementComponent->InitialSpeed = 3000.0f;
        //ProjectileMovementComponent->MaxSpeed = 3000.0f;
        ProjectileMovementComponent->InitialSpeed = 1.0f;
        ProjectileMovementComponent->MaxSpeed = 1.0f;
        ProjectileMovementComponent->bRotationFollowsVelocity = true;
        ProjectileMovementComponent->bShouldBounce = true;
        ProjectileMovementComponent->Bounciness = 0.3f;
        ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
    }

    if (!ProjectileMeshComponent)
    {
        ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
        static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("'/Game/TopDown/Meshes/Sphere.Sphere'"));
        if (Mesh.Succeeded())
        {
            ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
        }
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("'/Game/TopDown/Materials/SphereMaterial.SphereMaterial'"));
    if (Material.Succeeded())
    {
        ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
    }
    ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
    ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
    ProjectileMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::ShootInDirection(const FVector& ShootDirection)
{
    ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

