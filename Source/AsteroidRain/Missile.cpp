// Mauro García Monclú

#include "Missile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Asteroid.h"
#include "AsteroidsManager.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMissile::AMissile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(60.0f);
	RootComponent = CollisionComp;

	CollisionComp->SetNotifyRigidBodyCollision(true);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	CollisionComp->OnComponentHit.AddDynamic(this, &AMissile::OnHit);

	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("StaticMesh'/Game/Assets/Meshes/Missile/Missile.Missile'"));
	Mesh->SetStaticMesh(mesh.Object);

	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	Mesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	Mesh->RelativeScale3D = FVector(10.0f, 10.0f, 10.0f);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->UpdatedComponent = RootComponent;

	Movement->InitialSpeed = 3000.f;
	Movement->MaxSpeed = 3000.f;

	Movement->bRotationFollowsVelocity = true;
	Movement->bShouldBounce = false;
	Movement->ProjectileGravityScale = 0.0f;

	Movement->bConstrainToPlane = true;
	Movement->bSnapToPlaneAtStart = true;
	Movement->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);

	InitialLifeSpan = 10.0f;

}

void AMissile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this))
	{
		if (OtherActor->GetClass()->IsChildOf(AAsteroid::StaticClass()))
		{
			AAsteroid* asteroid = Cast<AAsteroid>(OtherActor);

			AAsteroidsManager* asteroidOwner = asteroid->GetOwnerAsteroid();
			int asteroidSize = asteroid->GetSize();
			FVector asteroidLocation = asteroid->GetActorLocation();

			AMyPlayerController* mpc = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			mpc->UpdateScore(10);

			asteroid->Destroy();

			if (asteroidSize > 1)
			{
				asteroidOwner->DestroyedByMissile(asteroidLocation, asteroidSize);

			}

			Destroy();

		}

	}

}
