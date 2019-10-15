// Mauro García Monclú

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS()
class ASTEROIDRAIN_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure)
		int GetScore();

	UFUNCTION(BlueprintCallable)
		void SetScore(int Score);
	
private:

	int Score;

};
