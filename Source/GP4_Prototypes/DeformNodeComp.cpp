// Fill out your copyright notice in the Description page of Project Settings.


#include "DeformNodeComp.h"

// Sets default values for this component's properties
UDeformNodeComp::UDeformNodeComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UDeformNodeComp::UpdateNodePos(float DeltaTime)
{
	auto targetLoc = GetOwner()->GetActorLocation() + localStartPos;
	auto currentLoc = GetComponentLocation();
	auto x = FMath::Lerp(currentLoc.X, targetLoc.X, DeltaTime * lerpSpeed);
	auto y = FMath::Lerp(currentLoc.Y, targetLoc.Y, DeltaTime * lerpSpeed);
	auto z = FMath::Lerp(currentLoc.Z, targetLoc.Z, DeltaTime * lerpSpeed);

	SetWorldLocation(FVector(x, y, z));
}


// Called when the game starts
void UDeformNodeComp::BeginPlay()
{
	Super::BeginPlay();

	localStartPos = GetRelativeLocation();
	
}


// Called every frame
void UDeformNodeComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

