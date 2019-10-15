//  Mauro García Monclú

#include "AsteroidsManager.h"
#include "Components/SceneComponent.h"
#include "Asteroid.h"
#include "Engine/World.h"

//Sets default values
AAsteroidsManager::AAsteroidsManager()
{
	//To use Tick()
	PrimaryActorTick.bCanEverTick = true;

	//SceneComponent so that SpawnLocation isn't the root
	RootLocation = CreateDefaultSubobject<USceneComponent>(TEXT("RootLocation"));
	RootComponent = RootLocation;

	RootLocation->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	//SceneComponent to spawn asteroid
	SpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnLocation"));
	SpawnLocation->SetupAttachment(RootComponent);

	SpawnLocation->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	//Initial the time for Tick() and auxiliar variables
	Time = 0.0f;
	AsteroidsPerSecondAccumulate = 0.0f;
	IncrementSpeed = 0.0f;

	AsteroidClass = TSubclassOf<AAsteroid>(AAsteroid::StaticClass());

}

//Called every frame
void AAsteroidsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime;

	//Action every second
	if (Time >= 1.0f)
	{
		AsteroidsPerSecond += 0.2;
		IncrementSpeed += 20.0f;

		//When you want spawn decimal part of asteroid, that is accumulated until is one unit or more
		if (AsteroidsPerSecondAccumulate < 1.0f)
		{
			AsteroidsPerSecondAccumulate += AsteroidsPerSecond;

		}

		if (AsteroidsPerSecondAccumulate >= 1.0f)
		{
			//Number of asteroid which you want spawn in one second
			for (int i = 0; i < (int)AsteroidsPerSecondAccumulate; i++)
			{
				//Change position and rotation of scene component which is used for location of spawn
				SpawnLocation->SetRelativeLocation(FVector(FMath::RandRange(-X, X), FMath::RandRange(-Y, Y), 0.0f));
				SpawnLocation->SetRelativeRotation(FRotator(FMath::RandRange(-180.0f, 180.0f), FMath::RandRange(-180.0f, 180.0f), FMath::RandRange(-180.0f, 180.0f)));

				//Randomize size
				int size = FMath::RandRange(1, 4);
				
				//Transform parameters of asteroids
				FTransform SpawnTransform = FTransform(FRotator((SpawnLocation->GetComponentToWorld()).GetRotation()), (SpawnLocation->GetComponentToWorld()).GetLocation(), FVector(2.5f*size, 2.5f*size, 2.5f*size));

				//Instance asteroid before spawn
				AAsteroid* currentAsteroid = GetWorld()->SpawnActorDeferred<AAsteroid>(AsteroidClass, SpawnTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding);
				
				if (currentAsteroid)
				{
					//Spawn asteroid
					currentAsteroid->FinishSpawning(SpawnTransform, true);
					
					//Velocity of asteroid about the place where it spawn and the rotation of manager
					//Initial velocity in case there is any error
					FVector velocity = FVector(1.0f, 1.0f, 0.0f);
					int32 maxIndex;
					TArray<float> componentsVelocity;

					//Get the main direction of velocity 
					componentsVelocity.Add(FMath::Abs((GetActorRotation().Vector()).X));
					componentsVelocity.Add(FMath::Abs((GetActorRotation().Vector()).Y));
					componentsVelocity.Add(FMath::Abs((GetActorRotation().Vector()).Z));

					FMath::Max<float>(componentsVelocity, &maxIndex);

					//Randomize the direction of velocity
					if (maxIndex == 0)
					{
						velocity = FVector((GetActorRotation().Vector()).X, FMath::RandRange(-1.0f, 1.0f), 0.0f);

					}
					else if (maxIndex == 1)
					{
						velocity = FVector(FMath::RandRange(-1.0f, 1.0f), (GetActorRotation().Vector()).Y, 0.0f);

					}

					currentAsteroid->IncrementSpeed(IncrementSpeed);

					//Change velocity, size and owner
					currentAsteroid->GeneratedVelocity(velocity);
					currentAsteroid->SetSize(size);
					currentAsteroid->SetOwnerAsteroid(this);

				}

			}

			//Get residual decimal part lacking
			AsteroidsPerSecondAccumulate -= (int)AsteroidsPerSecondAccumulate;

		}

		//Change next second
		Time = 0.0f;

	}

}

void AAsteroidsManager::DestroyedByMissile(FVector locationDestroyed, int size)
{
	float dimension = 40.0f * (float)size * 2.5f;

	bool isComplete = false;

	while (!isComplete)
	{
		FVector vectorVariant = FVector(FMath::RandRange(-dimension, dimension), FMath::RandRange(-dimension, dimension), 0.0f);
		
		int childSize = FMath::RandRange(1, size-1);

		FTransform SpawnTransform(FRotator((SpawnLocation->GetComponentToWorld()).GetRotation()), FVector(locationDestroyed.X + vectorVariant.X, locationDestroyed.Y + vectorVariant.Y, 0.0f), FVector(2.5f*childSize, 2.5f*childSize, 2.5f*childSize));
		
		//Instance asteroid before spawn
		AAsteroid* currentAsteroid = GetWorld()->SpawnActorDeferred<AAsteroid>(AsteroidClass, SpawnTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

		if (currentAsteroid)
		{
			//Spawn asteroid
			currentAsteroid->FinishSpawning(SpawnTransform, true);

			currentAsteroid->IncrementSpeed(IncrementSpeed);

			currentAsteroid->GeneratedVelocity(FVector(FMath::RandRange(-1.0f, 1.0f), FMath::RandRange(-1.0f, 1.0f), 0.0f));
			currentAsteroid->SetSize(childSize);
			currentAsteroid->SetOwnerAsteroid(this);

			if (currentAsteroid->GetActorLocation().Z != 0.0f)
			{
				currentAsteroid->SetActorLocation(FVector(currentAsteroid->GetActorLocation().X, currentAsteroid->GetActorLocation().Y, 0.0f), false, false, ETeleportType::TeleportPhysics);

			}

			size -= childSize;

		}

		if (size <= 0)
		{
			isComplete = true;

		}

	}

}
