// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraDriverComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP4_PROTOTYPES_API UCameraDriverComp : public UActorComponent
{
	GENERATED_BODY()

public:
		UCameraDriverComp();
	
		void Initalize(class USceneComponent* holder, class USpringArmComponent* arm);
	
		bool bInitalized = false;
	
		void UpdateCamera(const float deltaTime);

		void ReadCameraHorizontal(float value);
	
		void ReadCameraVertical(float value);
	
		void ReadCameraZoom(float value);
	
		void ToggleCameraFreeLook();
	
		bool GetbFreeCameraLook();
	protected:
	
		void UpdateCameraRotation(float DeltaTime);
	
		void UpdateCameraZoom(float DeltaTime);

		float GetPropVelocityChangeConstantDec(float deltaTime, float currentVelocity, float accelSpeed, float decelSpeed, bool changeCondition);
	
		void UpdateResetCamera(float DeltaTime);
	
		UPROPERTY(EditDefaultsOnly)
			float minCameraZoom = 100.f;
		UPROPERTY(EditDefaultsOnly)
			float maxCameraZoom = 2500.f;
	
		class USceneComponent* cameraHolder;
		class USpringArmComponent* cameraArm;
		//class ABoatPawn* owner;
	
		FTransform cameraHolderDefaultTransform;
		FTransform cameraArmDefaultTransform;
		float CameraRotationSpeed = 100.f;
		float CameraHorizontal = 0.f;
		float CameraVertical = 0.f;
	
		UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.0", ClampMax = "3.0", UIMin = "0.0", UIMax = "3.0"))
		float CameraResetStartTimerMax = 0.1f;
		UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float CameraResetSpeed = 0.2f;
	
		float CameraResetStartTimer = 0.f;
		float CameraResetTime = 0.f;
		
	
		float zoomDirection = 0;
		float zoomVelocity = 0;
		UPROPERTY(EditDefaultsOnly)
		float zoomSpeed = 700.f;
		float zoomDecelerationSpeed = 1.f;
		float zoomAccelerationSpeed = 800.f;
		bool bZoomAccOrDec = false;
	
		bool bFreeCameraLook = true;
		bool bShouldResetCamera = false;
		bool bNoHorizontalCamInput = false;
		bool bNoVerticalCamInput = false;
	
	public:
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};