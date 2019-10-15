// Mauro García Monclú

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

UCLASS()
class ASTEROIDRAIN_API AAsteroid : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* Movement;
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();

	void GeneratedVelocity(FVector VelocityDirection);

	void IncrementSpeed(float IncrementSpeed);

	class AAsteroidsManager* GetOwnerAsteroid();

	int GetSize();

	void SetOwnerAsteroid(class AAsteroidsManager* Owner);

	void SetSize(int Size);

private:

	class AAsteroidsManager* Owner;

	int Size;

};
