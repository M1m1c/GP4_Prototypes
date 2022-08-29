// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementComp.generated.h"


USTRUCT(Blueprintable)
struct FNavigationPlane
{
	GENERATED_BODY()
public:
	FNavigationPlane() {};
	FNavigationPlane(FVector forward, FVector right, FVector up )
	{
		forwardVector = forward;
		rightVector = right;
		upVector = up;
	};

	UPROPERTY(BlueprintReadOnly)
	FVector upVector = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly)
	FVector rightVector = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly)
	FVector forwardVector = FVector::ZeroVector;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP4_PROTOTYPES_API UMovementComp : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION()
		void ReadVertical(float value);
	UFUNCTION()
		void ReadHorizontal(float value);
	UFUNCTION()
		void InputPressJump();
	UFUNCTION()
		void InputReleaseJump();

	UMovementComp();
	void Initalize(class USceneComponent* cameraPivot);
	void UpdateMovement(float deltaTime);
	void UpdateNavigationPlane(FHitResult& hit);
	bool CheckTraceHits(TArray<FHitResult>& hits, bool shouldUpdateNavPlane);
	void LineTrace(TArray<FHitResult>& OutHits, FVector& start, FVector3d& end);
	struct FHitResult AttemptMove(FVector forceVector);
	bool IsJumping();
	float GetLinearVelocityChange(float deltaTime, float accelSpeed, float decelSpeed, bool changeCondition);
	float GetUpdatedStepSize(float DeltaTime, float speed, float& velocity, float input, bool bAccCondition);
	float GetVelocity(float DeltaTime, float currentVel, float input, bool bAccCondition);
	float GetProportionalVelocityChange(float deltaTime, float currentVelocity, float accelSpeed, float decelSpeed, bool changeCondition);

	UFUNCTION(BlueprintCallable)
	FVector GetMainForce() { return mainForce; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool bShouldResetNavPlane = false;
	bool bGrounded = false;
	float jumpTimer = 0.f;
	float maxJumpTimer = 0.4f;

	bool bJumpInputHeld = false;
	float jumpButtonHoldTimer = 0.f;

	bool bUpdateVertVelocity = false;
	bool bUpdateHoriVelocity = false;
	float verticalDirection = 0.f;
	float horizontalDirection = 0.f;
	FVector currentForward;
	FVector currentRight;
	UPROPERTY(BlueprintReadOnly)
	FNavigationPlane navigationPlane;

	AActor* owner;
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.0", ClampMax = "2.0", UIMin = "0.0", UIMax = "2.0"))
		float velAccelerationSpeed = 2.f;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.0", ClampMax = "2.0", UIMin = "0.0", UIMax = "2.0"))
	float velDecelerationSpeed = 1.f;

	UPROPERTY(EditDefaultsOnly)
	float maxSpeed = 20.f;

	float verticalVelocity=0.f;
	float horizontalVelocity=0.f;

	float gravity = -980.f;
	float accumulatedGravAccel = 1.f;
	float defaultGravityAccel = 1.f;

	class USceneComponent* cameraHolder;

	FVector mainForce;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
