//  Mauro Garc�a Moncl�

#include "AsteroidRainGameModeBase.h"
#include "MyPlayerController.h"
#include "Spaceship.h"

AAsteroidRainGameModeBase::AAsteroidRainGameModeBase()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = ASpaceship::StaticClass();
}
