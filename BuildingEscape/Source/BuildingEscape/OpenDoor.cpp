// Copyright jules evers 2018

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	// ...
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	thisDoor = GetOwner();
}

void UOpenDoor::OpenDoor()
{
	FRotator newRotation = FRotator(0.0f, 10.0f, 0.0f);
	thisDoor->SetActorRotation(newRotation);
}

void UOpenDoor::CloseDoor() 
{
	FRotator newRotation = FRotator(0.0f, -90.0f, 0.0f);
	thisDoor->SetActorRotation(newRotation);
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (pressurePlate->IsOverlappingActor(ActorThatOpens))
	{	
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > doorCloseDelay)
	{
		CloseDoor();
	}
}

