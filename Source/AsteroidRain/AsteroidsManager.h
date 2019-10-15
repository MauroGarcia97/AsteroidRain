//  Mauro García Monclú

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidsManager.generated.h"

UCLASS()
class ASTEROIDRAIN_API AAsteroidsManager : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Root, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* RootLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawn, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* SpawnLocation;
	
public:

	AAsteroidsManager();

	//Size of component X to spawn asteroids
	UPROPERTY(EditInstanceOnly)
		float X;
		
	//Size of component Y to spawn asteroids
	UPROPERTY(EditInstanceOnly)
		float Y;

	//Frecuency with asteroid spawn per second
	UPROPERTY(EditInstanceOnly)
		float AsteroidsPerSecond;

	virtual void Tick(float DeltaTime) override;

	void DestroyedByMissile(FVector Location, int Size);

private:

	float Time;

	float AsteroidsPerSecondAccumulate;

	float IncrementSpeed;

	TSubclassOf<class AAsteroid> AsteroidClass;
	
};
