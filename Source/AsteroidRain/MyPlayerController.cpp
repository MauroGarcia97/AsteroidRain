// Mauro García Monclú

#include "MyPlayerController.h"
#include "Spaceship.h"
#include "MyGameInstance.h"

AMyPlayerController::AMyPlayerController()
{
	/*If there is Tick()*/
	PrimaryActorTick.bCanEverTick = true;

	Life = 1.0f;

	Score = 0;

	DeltaTimeAccumulate = 0.0f;

}

// Called every frame
void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeltaTimeAccumulate += DeltaTime;

	if (DeltaTimeAccumulate >= 1.0f)
	{
		Score++;

		DeltaTimeAccumulate = 0.0f;

	}

}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AMyPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);

	InputComponent->BindAction("Shoot", IE_Pressed, this, &AMyPlayerController::Shoot);

}

void AMyPlayerController::MoveForward(float value)
{
	ASpaceship* pawn = Cast<ASpaceship>(this->GetPawn());

	if (pawn)
	{
		pawn->MoveForward(value);

	}

}

void AMyPlayerController::MoveRight(float value)
{
	ASpaceship* pawn = Cast<ASpaceship>(this->GetPawn());

	if (pawn)
	{
		pawn->MoveRight(value);

	}

}

void AMyPlayerController::Shoot()
{
	ASpaceship* pawn = Cast<ASpaceship>(this->GetPawn());

	if (pawn)
	{
		pawn->Shoot();

	}

}

float AMyPlayerController::GetLife()
{
	return Life;

}

int AMyPlayerController::GetScore()
{
	return Score;

}

void AMyPlayerController::UpdateLife(float uLife)
{
	Life += uLife;

}

void AMyPlayerController::UpdateScore(int uScore)
{
	Score += uScore;

}
