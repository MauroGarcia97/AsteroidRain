// Mauro García Monclú

#include "MyPlayerController.h"
#include "Spaceship.h"

//#include "Engine.h"
/*if (GEngine)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Hola")));
}*/

AMyPlayerController::AMyPlayerController()
{
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
	auto pawn = Cast<ASpaceship>(this->GetPawn());

	if (pawn)
	{
		pawn->MoveForward(value);

	}

}

void AMyPlayerController::MoveRight(float value)
{
	auto pawn = Cast<ASpaceship>(this->GetPawn());

	if (pawn)
	{
		pawn->MoveRight(value);

	}

}

void AMyPlayerController::Shoot()
{

	auto pawn = Cast<ASpaceship>(this->GetPawn());

	if (pawn)
	{
		pawn->Shoot();

	}
}
