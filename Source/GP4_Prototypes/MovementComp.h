// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP4_PROTOTYPES_API UMovementComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovementComp();
	void Initalize(class USceneComponent* cameraPivot);
	void UpdateMovement(float deltaTime);
	void ReadVertical(float value);
	void ReadHorizontal(float value);
	float GetLinearVelocityChange(float deltaTime, float accelSpeed, float decelSpeed, bool changeCondition);
	float GetUpdatedStepSize(float DeltaTime, float speed, float& velocity, float input, bool bAccCondition);
	float GetVelocity(float DeltaTime, float currentVel, float input, bool bAccCondition);
	float GetProportionalVelocityChange(float deltaTime, float currentVelocity, float accelSpeed, float decelSpeed, bool changeCondition);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	bool bUpdateVertVelocity = false;
	bool bUpdateHoriVelocity = false;
	float verticalDirection = 0.f;
	float horizontalDirection = 0.f;

	AActor* owner;
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float velAccelerationSpeed = 0.3f;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float velDecelerationSpeed = 0.05f;

	UPROPERTY(EditDefaultsOnly)
	float maxSpeed = 10.f;

	float verticalVelocity=0.f;
	float horizontalVelocity=0.f;

	class USceneComponent* cameraHolder;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
