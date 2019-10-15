// Mauro García Monclú

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Spaceship.generated.h"

UCLASS()
class ASTEROIDRAIN_API ASpaceship : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SkeletalMesh, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Missile, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* SpawnLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UFloatingPawnMovement* Movement;

public:
	// Sets default values for this character's properties
	ASpaceship();
	
	//Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);

	void MoveRight(float value);

	void Shoot();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:

	float Time;

	bool Cooldown;

	TSubclassOf<class AMissile> MissileClass;

	FActorSpawnParameters ActorSpawnParams;

	class AMyPlayerController* MyPlayerController;
	
};
