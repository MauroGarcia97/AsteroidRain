//  Mauro García Monclú

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidsManager.generated.h"

UCLASS()
class ASTEROIDRAIN_API AAsteroidsManager : public AActor
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* SpawnLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* RootLocation;
	
public:	
	// Sets default values for this actor's properties
	AAsteroidsManager();

	UPROPERTY(EditInstanceOnly)
		float X;
		
	UPROPERTY(EditInstanceOnly)
		float Y;

	UPROPERTY(EditInstanceOnly)
	int AsteroidsPerSecond;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TSubclassOf<class AAsteroid> AsteroidClass;
	FActorSpawnParameters ActorSpawnParams;

	float Time;
	
};
