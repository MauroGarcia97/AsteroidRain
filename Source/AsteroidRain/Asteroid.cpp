// Mauro García Monclú

#include "Asteroid.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AAsteroid::AAsteroid()
{
	/*If there is Tick()
	PrimaryActorTick.bCanEverTick = true;*/
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("StaticMesh'/Game/Assets/Meshes/Asteroid/Asteroid.Asteroid'"));
	Mesh->SetStaticMesh(mesh.Object);
	Mesh->RelativeScale3D = FVector(10.0f, 10.0f, 10.0f);

}

/*void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

}*/

/*void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/
