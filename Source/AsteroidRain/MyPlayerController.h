//  Mauro García Monclú

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

UCLASS()
class ASTEROIDRAIN_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:

	AMyPlayerController();

	//Called every frame
	virtual void Tick(float DeltaTime) override;

	//Called to bind functionality to input
	virtual void SetupInputComponent() override;

	void MoveForward(float Value);

	void MoveRight(float value);

	void Shoot();

	UFUNCTION(BlueprintPure)
		float GetLife();

	UFUNCTION(BlueprintPure)
		int GetScore();

	void UpdateLife(float Life);

	void UpdateScore(int Score);

private:

	float Life;

	int Score;

	float DeltaTimeAccumulate;
	
};
