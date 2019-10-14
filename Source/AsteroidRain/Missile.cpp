// Fill out your copyright notice in the Description page of Project Settings.

#include "Missile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Asteroid.h"
#include "AsteroidsManager.h"

#include "Engine.h"
// Sets default values
AMissile::AMissile()
{
	/*If there is Tick()
	PrimaryActorTick.bCanEverTick = true;*/
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(60.0f);
	RootComponent = CollisionComp;
	CollisionComp->SetNotifyRigidBodyCollision(true);
	CollisionComp->BodyInstance.SetCollisionProfileName("OverlapAll");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMissile::OnOverlapBegin);
	CollisionComp->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

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

	OneTime = true;
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AMissile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && OneTime)
	{
		OneTime = false;
		if (OtherActor->GetClass()->IsChildOf(AAsteroid::StaticClass()))
		{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Hola")));
		}
			auto asteroid = Cast<AAsteroid>(OtherActor);
			int asteroidSize = asteroid->Size;
			asteroid->Destroy();
			if (asteroidSize > 1)
			{
				auto asteroidOwner = asteroid->Owner;
				FVector asteroidLocation = asteroid->GetActorLocation();
				/*while (asteroid)
				{

				}*/
				asteroidOwner->DestroyedByMissile(asteroidLocation, asteroidSize);
			}
			Destroy();
		}
	}
}
