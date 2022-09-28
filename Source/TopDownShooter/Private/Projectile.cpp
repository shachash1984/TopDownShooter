// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Net/UnrealNetwork.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

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

        CollisionComponent->SetNetAddressable();
		CollisionComponent->SetIsReplicated(true);

        // Set the Root component to be the collision component
        RootComponent = CollisionComponent;
    }

    if (!ProjectileMovementComponent)
    {
	    // Use this component to drive this projectile's movement
        ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
        ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
        ProjectileMovementComponent->InitialSpeed = InitialSpeed;
        ProjectileMovementComponent->MaxSpeed = 1000.0f;
        ProjectileMovementComponent->bRotationFollowsVelocity = true;
        ProjectileMovementComponent->bShouldBounce = true;
        ProjectileMovementComponent->Bounciness = 0.3f;
        ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
        ProjectileMovementComponent->SetNetAddressable();
        ProjectileMovementComponent->SetIsReplicated(true);
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
		ProjectileMaterialInstance->SetVectorParameterValue("Color", FLinearColor::Black);
    }
    ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
    ProjectileMeshComponent->SetRelativeScale3D(FVector(0.05f, 0.02f, 0.02f));
    ProjectileMeshComponent->SetupAttachment(RootComponent);
    //ProjectileMeshComponent->SetNetAddressable();
    //ProjectileMeshComponent->SetIsReplicated(true);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(5.0f);
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

void AProjectile::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME( AProjectile, ProjectileMeshComponent );
    DOREPLIFETIME( AProjectile, ProjectileMovementComponent );
    DOREPLIFETIME( AProjectile, CollisionComponent );
}

