// Fill out your copyright notice in the Description page of Project Settings.

#include "Spaceship.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Missile.h"

#include "Engine.h"

//Sets default values
ASpaceship::ASpaceship()
{
	/*If there is Tick()*/
	//PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(100.0f);
	RootComponent = CollisionComp;

	CollisionComp->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	CollisionComp->SetCollisionProfileName("BlockAll");

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

	MissileClass = TSubclassOf<AMissile>(AMissile::StaticClass());

	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	Time = 0.0f;

	Cooldown = false;

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

// Called when the game starts or when spawned
void ASpaceship::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime;

	//Action every second
	if (Time >= 0.5f)
	{
		Cooldown = false;
		Time = 0.0f;

	}
}
