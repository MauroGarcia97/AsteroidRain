// Mauro García Monclú

#include "Spaceship.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "Missile.h"
#include "Asteroid.h"
#include "MyPlayerController.h"

//Sets default values
ASpaceship::ASpaceship()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(100.0f);
	RootComponent = CollisionComp;

	CollisionComp->SetNotifyRigidBodyCollision(true);
	CollisionComp->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	CollisionComp->SetCollisionProfileName("BlockAll");

	CollisionComp->OnComponentHit.AddDynamic(this, &ASpaceship::OnHit);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletal(TEXT("SkeletalMesh'/Game/Assets/Meshes/Spaceship/Spaceship.Spaceship'"));
	SkeletalMesh->SkeletalMesh = skeletal.Object;

	SkeletalMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	SkeletalMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	SkeletalMesh->RelativeScale3D = FVector(10.0f, 10.0f, 10.0f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(RootComponent);

	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->RelativeRotation = FRotator(-90.0f, 0.0f, 0.0f);
	FollowCamera->RelativeLocation = FVector(0.0f, 0.0f, 4000.0f);

	//SceneComponent to spawn missile
	SpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnLocation"));
	SpawnLocation->SetupAttachment(RootComponent);
	SpawnLocation->SetRelativeLocation(FVector(175.0f, 0.0f, 0.0f));

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	Movement->UpdatedComponent = RootComponent;

	Movement->Velocity = FVector(0.0f, 0.0f, 0.0f);
	Movement->MaxSpeed = 1000.0f;

	Movement->bConstrainToPlane = true;
	Movement->bSnapToPlaneAtStart = true;
	Movement->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);

	Time = 0.0f;

	Cooldown = false;
	
	MissileClass = TSubclassOf<AMissile>(AMissile::StaticClass());

	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

	MyPlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

}

//Called every frame
void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime;

	//Action every half second
	if (Time >= 0.5f)
	{
		//Disable cooldown
		Cooldown = false;

		Time = 0.0f;

	}

}

void ASpaceship::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);

}

void ASpaceship::MoveRight(float value)
{
	SetActorRotation(FMath::Lerp(GetActorRotation(), GetActorRotation() + FRotator(0.0f, value, 0.0f), 1.0f));

}

void ASpaceship::Shoot()
{
	if (!Cooldown)
	{
		AMissile* currentMissile = GetWorld()->SpawnActor<AMissile>(MissileClass, (SpawnLocation->GetComponentToWorld()).GetLocation(), FRotator((SpawnLocation->GetComponentToWorld()).GetRotation()), ActorSpawnParams);

		if (currentMissile != NULL)
		{
			Cooldown = true;

		}

	}

}

void ASpaceship::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this))
	{
		if (OtherActor->GetClass()->IsChildOf(AAsteroid::StaticClass()))
		{
			AAsteroid* asteroid = Cast<AAsteroid>(OtherActor);

			MyPlayerController->UpdateLife(-((float)(asteroid->GetSize()))/4.0f);

			OtherActor->Destroy();

		}

	}

}
