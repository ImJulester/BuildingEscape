// Copyright jules evers 2018

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
	

	///lookfor attached physics handle
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	input = GetOwner()->FindComponentByClass<UInputComponent>();

	if (!physicsHandle) 
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName());
	}
	if (!input)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName());
	}
	else 
	{
		input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
}

void UGrabber::Grab() 
{
	//grab
	UE_LOG(LogTemp, Warning, TEXT("Grab"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector playerViewPointPos;
	FRotator playerViewPointRot;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerViewPointPos, playerViewPointRot);
	//get player viewpoint
	/*UE_LOG(LogTemp, Warning, TEXT("player pos = %s player rot = %s"), *playerViewPointPos.ToString(), *playerViewPointRot.ToString());*/

	FVector lineTraceEnd = playerViewPointPos + playerViewPointRot.Vector() * grabReach;
	DrawDebugLine(GetWorld(), playerViewPointPos, lineTraceEnd, FColor(255, 0, 0), false, 0.0f, 0, 10);
	
	//Setup query parameters
	FCollisionQueryParams raycastParams(FName(TEXT("")), false, GetOwner());

	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(hit, playerViewPointPos, lineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), raycastParams);
	
	if (hit.GetActor()) 
	{
		UE_LOG(LogTemp, Warning, TEXT("hit name %s"), *hit.GetActor()->GetName());
	}

}

