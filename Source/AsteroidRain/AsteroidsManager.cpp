//  Mauro García Monclú

#include "AsteroidsManager.h"
#include "Components/SceneComponent.h"
#include "Asteroid.h"
#include "Engine/World.h"
#include "Engine.h"

// Sets default values
AAsteroidsManager::AAsteroidsManager()
{
	//If there is Tick()
	PrimaryActorTick.bCanEverTick = true;

	RootLocation = CreateDefaultSubobject<USceneComponent>(TEXT("RootLocation"));
	RootComponent = RootLocation;
	RootLocation->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	SpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnLocation"));
	SpawnLocation->SetupAttachment(RootComponent);
	SpawnLocation->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	Time = 0.0f;
	AsteroidClass = TSubclassOf<AAsteroid>(AAsteroid::StaticClass());
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

}

// Called when the game starts or when spawned
void AAsteroidsManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAsteroidsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime;

	if (Time >= 1.0f)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Hola")));
		}
		for (int i = 0; i < AsteroidsPerSecond; i++)
		{
			SpawnLocation->SetRelativeLocation(FVector(FMath::RandRange(-X, X), FMath::RandRange(-Y, Y), 0.0f));
			GetWorld()->SpawnActor<AAsteroid>(AsteroidClass, (SpawnLocation->GetComponentToWorld()).GetLocation(), FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);


		}


		Time = 0.0f;

	}
}

