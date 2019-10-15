// Mauro García Monclú

#include "Asteroid.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"

AAsteroid::AAsteroid()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(100.0f);
	RootComponent = CollisionComp;

	CollisionComp->SetNotifyRigidBodyCollision(true);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	CollisionComp->SetGenerateOverlapEvents(true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("StaticMesh'/Game/Assets/Meshes/Asteroid/Asteroid.Asteroid'"));
	Mesh->SetStaticMesh(mesh.Object);

	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	Mesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	Mesh->RelativeScale3D = FVector(1.0f, 1.0f, 1.0f);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->UpdatedComponent = RootComponent;
	Movement->InitialSpeed = 2000.f;
	Movement->MaxSpeed = 2000.f;

	Movement->bRotationFollowsVelocity = true;
	Movement->bShouldBounce = true;
	Movement->ProjectileGravityScale = 0.0f;

	Movement->bConstrainToPlane = true;
	Movement->bSnapToPlaneAtStart = true;
	Movement->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);

	InitialLifeSpan = 120.0f;

	Size = 1;
	Owner = NULL;

}

void AAsteroid::GeneratedVelocity(FVector nVelocityDirection)
{
	float sizeVelocity = FMath::RandRange(Movement->MaxSpeed/2.0f, Movement->MaxSpeed);

	nVelocityDirection.Normalize();
	Movement->Velocity = FRotator(0.0f, 90.0f, 0.0f).RotateVector(nVelocityDirection*sizeVelocity);

}

void AAsteroid::IncrementSpeed(float incrementSpeed)
{
	Movement->MaxSpeed += incrementSpeed;

}

AAsteroidsManager* AAsteroid::GetOwnerAsteroid()
{
	return Owner;

}

int AAsteroid::GetSize()
{
	return Size;

}

void AAsteroid::SetOwnerAsteroid(class AAsteroidsManager* nOwner)
{
	Owner = nOwner;

}

void AAsteroid::SetSize(int nSize)
{
	Size = nSize;

}
