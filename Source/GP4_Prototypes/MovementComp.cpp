// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementComp.h"

// Sets default values for this component's properties
UMovementComp::UMovementComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMovementComp::Initalize(USceneComponent* cameraPivot)
{
	owner = GetOwner();
	if (!ensure(owner)) { return; }
	cameraHolder = cameraPivot;
	if (!ensure(cameraHolder)) { return; }
}

void UMovementComp::UpdateMovement(float deltaTime)
{
	auto newVertStep = bUpdateVertVelocity ? deltaTime * verticalDirection * velAccelerationSpeed : 0.f;
	auto newHoriStep = bUpdateHoriVelocity ? deltaTime * horizontalDirection * velAccelerationSpeed : 0.f;

	auto forwardVelocity = currentForward * newVertStep;
	auto rightVelocity = currentRight * newHoriStep;

	auto force = forwardVelocity + rightVelocity;
	//auto cross = FVector::CrossProduct(mainForce.GetSafeNormal(), force.GetSafeNormal());

	mainForce += force;
	mainForce = mainForce.GetClampedToMaxSize(1.f);

	float RemainingTime = deltaTime;
	int Iterations = 0;

	while (RemainingTime > 0.f && ++Iterations < 10)
	{		
		auto hit = AttemptMove();
		auto ownerLocation = owner->GetActorLocation();

		if (hit.bBlockingHit)
		{

			auto normal2D = FVector(hit.Normal.X, hit.Normal.Y, 0.f);

			if (hit.bStartPenetrating)
			{
				owner->AddActorWorldOffset(normal2D * (hit.PenetrationDepth + 0.1f));
			}
			else
			{
				mainForce= FVector::VectorPlaneProject(mainForce, normal2D);
				RemainingTime -= RemainingTime * hit.Time;
			}
		}
		else
		{	
			break;
		}
	}


	if (!bUpdateVertVelocity && !bUpdateHoriVelocity)
	{
		auto reductionForce = (mainForce.GetSafeNormal() * -1.f) * velDecelerationSpeed * deltaTime;
		auto resultForce = (reductionForce + mainForce);
		if (FVector::DotProduct(resultForce.GetSafeNormal(), mainForce.GetSafeNormal()) < 0.f)
		{
			mainForce = FVector::ZeroVector;
		}
		else 
		{

			mainForce += reductionForce;
		}
	}

}

FHitResult UMovementComp::AttemptMove()
{
	FHitResult hit;
	owner->AddActorWorldOffset(
		mainForce.GetSafeNormal() * (FMath::Clamp(mainForce.Size(), 0.f, 1.f) * maxSpeed),
		true,
		&hit);
	return hit;
}

void UMovementComp::ReadVertical(float value)
{
	if (FMath::IsNearlyZero(value))
	{
		bUpdateVertVelocity = false;
		return;
	}
	verticalDirection = FMath::Clamp(value, -1.f, 1.f);
	currentForward = cameraHolder->GetForwardVector();
	bUpdateVertVelocity = true;
}

void UMovementComp::ReadHorizontal(float value)
{
	if (FMath::IsNearlyZero(value))
	{
		bUpdateHoriVelocity = false;
		return;
	}
	horizontalDirection = FMath::Clamp(value, -1.f, 1.f);
	currentRight = cameraHolder->GetRightVector();
	bUpdateHoriVelocity = true;
}



float UMovementComp::GetUpdatedStepSize(float DeltaTime, float speed, float& velocity, float input, bool bAccCondition)
{
	velocity = GetVelocity(DeltaTime, velocity, input, bAccCondition);
	return speed * velocity;
}

float  UMovementComp::GetVelocity(float DeltaTime, float currentVel, float input, bool bAccCondition)
{
	auto bNegativeInput = input < 0.f;
	auto bNegativeVelocity = currentVel < 0.f;
	auto acc = bNegativeInput ? -velAccelerationSpeed : velAccelerationSpeed;
	auto dec = bNegativeVelocity ? velDecelerationSpeed : -velDecelerationSpeed;

	auto velocityChange = GetProportionalVelocityChange(
		DeltaTime,
		currentVel,
		acc,
		dec,
		bAccCondition);

	auto newVelocity = FMath::Clamp(currentVel + velocityChange, -1.f, 1.f);

	auto possitiveClamp = FMath::Clamp(newVelocity, 0.f, 1.f);
	auto negativeClamp = FMath::Clamp(newVelocity, -1.f, 0.f);
	auto clampedResult = bNegativeVelocity ? negativeClamp : possitiveClamp;

	return bAccCondition ? newVelocity : clampedResult;
}

float UMovementComp::GetProportionalVelocityChange(float deltaTime, float currentVelocity, float accelSpeed, float decelSpeed, bool changeCondition)
{
	auto proportionalDec = (deltaTime + (deltaTime * (decelSpeed * currentVelocity)));
	proportionalDec = decelSpeed < 0.f ? -proportionalDec : proportionalDec;
	auto velocityChange = (changeCondition ? deltaTime * accelSpeed : proportionalDec);
	return velocityChange;
}

float UMovementComp::GetLinearVelocityChange(float deltaTime, float accelSpeed, float decelSpeed, bool changeCondition)
{
	auto velocityChange = (changeCondition ? deltaTime * accelSpeed : -(deltaTime * decelSpeed));
	return velocityChange;
}

// Called when the game starts
void UMovementComp::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UMovementComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

